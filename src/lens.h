#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include "../../Eigen/Eigen/Core"

#include "../../polynomial-optics/src/raytrace.h"

#ifndef M_PI
#  define M_PI 3.14159265358979323846
#endif


static inline void common_sincosf(float phi, float *sin, float *cos) {
  *sin = std::sin(phi);
  *cos = std::cos(phi);
}


// helper function for dumped polynomials to compute integer powers of x:
static inline float lens_ipow(const float x, const int exp) {
  if(exp == 0) return 1.0f;
  if(exp == 1) return x;
  if(exp == 2) return x*x;
  const float p2 = lens_ipow(x, exp/2);
  if(exp &  1) return x * p2 * p2;
  return p2 * p2;
}


inline void load_lens_constants (Camera *camera)
{
  switch (camera->lensModel){
    #include "auto_generated_lens_includes/load_lens_constants.h"
  }
}

// evaluates from sensor (in) to outer pupil (out).
// input arrays are 5d [x,y,dx,dy,lambda] where dx and dy are the direction in
// two-plane parametrization (that is the third component of the direction would be 1.0).
// units are millimeters for lengths and micrometers for the wavelength (so visible light is about 0.4--0.7)
// returns the transmittance computed from the polynomial.
static inline float lens_evaluate(const Eigen::VectorXf in, Eigen::VectorXf &out, Camera *camera)
{
  const float x = in[0], y = in[1], dx = in[2], dy = in[3], lambda = in[4];
  float out_transmittance = 0.0;
  switch (camera->lensModel){
    #include "auto_generated_lens_includes/load_pt_evaluate.h"
  }

  return std::max(0.0f, out_transmittance);
}

/*
// evaluates from the sensor (in) to the aperture (out) only
// returns the transmittance.
static inline float lens_evaluate_aperture(const float *in, float *out)
{
  const float x = in[0], y = in[1], dx = in[2], dy = in[3], lambda = in[4];
#include "pt_evaluate_aperture.h"
  out[0] = out_x; out[1] = out_y; out[2] = out_dx; out[3] = out_dy;
  return std::max(0.0f, out_transmittance);
}
*/


// solves for the two directions [dx,dy], keeps the two positions [x,y] and the
// wavelength, such that the path through the lens system will be valid, i.e.
// lens_evaluate_aperture(in, out) will yield the same out given the solved for in.
// in: point on sensor. out: point on aperture.
static inline void lens_pt_sample_aperture(Eigen::VectorXf &in, Eigen::VectorXf &out, float dist, Camera *camera)
{
  float out_x = out[0], out_y = out[1], out_dx = out[2], out_dy = out[3], out_transmittance = 1.0f;
  float x = in[0], y = in[1], dx = in[2], dy = in[3], lambda = in[4];

  switch (camera->lensModel){
    #include "auto_generated_lens_includes/load_pt_sample_aperture.h"
  }

  // directions may have changed, copy all to be sure.
  out[0] = out_x; // dont think this is needed
  out[1] = out_y; // dont think this is needed
  out[2] = out_dx;
  out[3] = out_dy;

  in[0] = x; // dont think this is needed
  in[1] = y; // dont think this is needed
  in[2] = dx;
  in[3] = dy;
}



// solves for a sensor position given a scene point and an aperture point
// returns transmittance from sensor to outer pupil
static inline float lens_lt_sample_aperture(
    const Eigen::Vector3f scene,   // 3d point in scene in camera space
    const Eigen::Vector2f ap,      // 2d point on aperture (in camera space, z is known)
    Eigen::VectorXf &sensor,        // output point and direction on sensor plane/plane
    Eigen::VectorXf &out,           // output point and direction on outer pupil
    const float lambda,   // wavelength
    Camera *camera)   
{
  const float scene_x = scene[0], scene_y = scene[1], scene_z = scene[2];
  const float ap_x = ap[0], ap_y = ap[1];
  float x = 0, y = 0, dx = 0, dy = 0;

  switch (camera->lensModel){
    #include "auto_generated_lens_includes/load_lt_sample_aperture.h"    
  }

  sensor[0] = x; sensor[1] = y; sensor[2] = dx; sensor[3] = dy; sensor[4] = lambda;
  return std::max(0.0f, out[4]);

}

/*
// jacobian of polynomial mapping sensor to outer pupil. in[]: sensor point/direction/lambda.
static inline void lens_evaluate_jacobian(const float *in, float *J)
{
  const float x = in[0], y = in[1], dx = in[2], dy = in[3], lambda = in[4];
#include "pt_evaluate_jacobian.h"
  J[0]  = dx00; J[1]  = dx01; J[2]  = dx02; J[3]  = dx03; J[4]  = dx04;
  J[5]  = dx10; J[6]  = dx11; J[7]  = dx12; J[8]  = dx13; J[9]  = dx14;
  J[10] = dx20; J[11] = dx21; J[12] = dx22; J[13] = dx23; J[14] = dx24;
  J[15] = dx30; J[16] = dx31; J[17] = dx32; J[18] = dx33; J[19] = dx34;
  J[20] = dx40; J[21] = dx41; J[22] = dx42; J[23] = dx43; J[24] = dx44;
}*/

/*
static inline float lens_det_sensor_to_outer_pupil(const float *sensor, const float *out, const float focus)
{
  float J[25];
  lens_evaluate_jacobian(sensor, J);
  // only interested in how the direction density at the sensor changes wrt the vertex area on the output
  float T[25] = {
    1., 0., focus, 0., 0.,
    0., 1., 0., focus, 0.,
    0., 0., 1., 0., 0.,
    0., 0., 0., 1., 0.,
    0., 0., 0., 0., 1.};
  float JT[25] = {0.};
  for(int i=2;i<4;i++) // only interested in 2x2 subblock.
    for(int j=0;j<2;j++)
      for(int k=0;k<4;k++)
        JT[i+5*j] += J[k + 5*j] * T[i + 5*k];
  const float det = JT[2] * JT[5+3] - JT[3] * JT[5+2];

  // convert from projected disk to point on hemi-sphere
  const float R = lens_outer_pupil_curvature_radius;
  const float deto = std::sqrt(R*R-out[0]*out[0]-out[1]*out[1])/R;
  // there are two spatial components which need conversion to dm:
  const float dm2mm = 100.0f;
  return fabsf(det * deto) / (dm2mm*dm2mm);
}*/

/*
static inline void lens_evaluate_aperture_jacobian(const float *in, float *J)
{
  const float x = in[0], y = in[1], dx = in[2], dy = in[3], lambda = in[4];
#include "pt_evaluate_aperture_jacobian.h"
  J[0]  = dx00; J[1]  = dx01; J[2]  = dx02; J[3]  = dx03; J[4]  = dx04;
  J[5]  = dx10; J[6]  = dx11; J[7]  = dx12; J[8]  = dx13; J[9]  = dx14;
  J[10] = dx20; J[11] = dx21; J[12] = dx22; J[13] = dx23; J[14] = dx24;
  J[15] = dx30; J[16] = dx31; J[17] = dx32; J[18] = dx33; J[19] = dx34;
  J[20] = dx40; J[21] = dx41; J[22] = dx42; J[23] = dx43; J[24] = dx44;
}*/


// xorshift fast random number generator
inline uint32_t xor128(void){
  static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
  uint32_t t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19) ^ t ^ (t >> 8));
}

/*
inline float Lerp(float t, float v1, float v2) {
  return (1.0f - t) * v1 + t * v2;
}
*/

// sin approximation, not completely accurate but faster than std::sin
inline float fastSin(float x){
  x = fmod(x + M_PI, M_PI * 2) - M_PI; // restrict x so that -M_PI < x < M_PI
  const float B = 4.0f / M_PI;
  const float C = -4.0f / (M_PI*M_PI);
  float y = B * x + C * x * std::abs(x);
  const float P = 0.225f;
  return P * (y * std::abs(y) - y) + y;
}


inline float fastCos(float x){
  // conversion from sin to cos
  x += M_PI * 0.5;

  x = fmod(x + M_PI, M_PI * 2) - M_PI; // restrict x so that -M_PI < x < M_PI
  const float B = 4.0f / M_PI;
  const float C = -4.0f / (M_PI*M_PI);
  float y = B * x + C * x * std::abs(x);
  const float P = 0.225f;
  return P * (y * std::abs(y) - y) + y;
}


// maps points on the unit square onto the unit disk uniformly
inline void concentric_disk_sample(const float ox, const float oy, Eigen::Vector2d &lens, bool fast_trigo)
{
  float phi, r;

  // switch coordinate space from [0, 1] to [-1, 1]
  float a = 2.0 * ox - 1.0;
  float b = 2.0 * oy - 1.0;

  if ((a * a) > (b * b)){
    r = a;
    phi = (0.78539816339f) * (b / a);
  }
  else {
    r = b;
    phi = (M_PI/2.0f)-(0.78539816339f) * (a / b);
  }

  if (!fast_trigo){
    lens(0) = r * std::cos(phi);
    lens(1) = r * std::sin(phi);
  } else {
    lens(0) = r * fastCos(phi);
    lens(1) = r * fastSin(phi);
  }
}


static inline void lens_sample_aperture(float &x, float &y, float r1, float r2, const float radius, const int blades)
{
  const int tri = (int)(r1*blades);

  // rescale:
  r1 = r1*blades - tri;

  // sample triangle:
  float a = std::sqrt(r1);
  float b = (1.0f-r2)*a;
  float c = r2*a;

  float p1[2], p2[2];

  common_sincosf(2.0f*M_PI/blades * (tri+1), p1, p1+1);
  common_sincosf(2.0f*M_PI/blades * tri, p2, p2+1);

  x = radius * (b * p1[1] + c * p2[1]);
  y = radius * (b * p1[0] + c * p2[0]);
}


/*
static inline int lens_clip_aperture(const float x, const float y, const float radius, const int blades)
{ 
  // early out
  if(x*x + y*y > radius*radius) return 0;
  float xx = radius; 
  float yy = 0.0f;
  for(int b=1;b<blades+1;b++)
  {   
  float tmpx, tmpy;
  common_sincosf(2.0f*(float)M_PI/blades * b, &tmpy, &tmpx);
  tmpx *= radius;
  tmpy *= radius;
  const float normalx = xx + tmpx;
  const float normaly = yy + tmpy;
  float dot0 = (normalx)*(x-xx) + (normaly)*(y-yy);
  if(dot0 > 0.0f) return 0;
  xx = tmpx;
  yy = tmpy;
  }
  return 1;
}*/


/*
static inline float lens_det_aperture_to_sensor(const float *sensor, const float focus)
{ 
  float J[25];
  lens_evaluate_aperture_jacobian(sensor, J);
  // only interested in how the directional density at the sensor changes wrt the vertex area (spatial) at the aperture
  float T[25] = {
  1., 0., focus, 0., 0.,
  0., 1., 0., focus, 0.,
  0., 0., 1., 0., 0.,
  0., 0., 0., 1., 0.,
  0., 0., 0., 0., 1.};
  float JT[25] = {0.};
  for(int i=2;i<4;i++) // only interested in 2x2 subblock.
  for(int j=0;j<2;j++)
    for(int k=0;k<4;k++)
    JT[i+5*j] += J[k + 5*j] * T[i + 5*k];
  const float det = fabsf(JT[2] * JT[5+3] - JT[3] * JT[5+2]);
  // there are two spatial components which need conversion to dm:
  const float dm2mm = 100.0f;
  return dm2mm*dm2mm/det;
}*/

/*
static inline float lens_aperture_area(const float radius, const int blades)
{
  const float tri = .5f*radius * radius * sinf(2.0f*AI_PI/(float)blades);
  return blades * tri;
}*/








// returns sensor offset in mm
// traces rays backwards through the lens
float camera_set_focus(float dist, Camera *camera)
{
  const Eigen::Vector3f target(0, 0, dist);
  Eigen::VectorXf sensor(5); sensor.setZero();
  Eigen::VectorXf out(5); out.setZero();
  sensor(4) = camera->lambda;
  float offset = 0.0f;
  int count = 0;
  const float scale_samples = 0.1f;
  Eigen::Vector2f aperture(0,0);

  const int S = 4;

  // trace a couple of adjoint rays from there to the sensor and
  // see where we need to put the sensor plane.
  for(int s=1; s<=S; s++){
    for(int k=0; k<2; k++){
      
      // reset aperture
      aperture.setZero();

      aperture[k] = camera->lens_aperture_housing_radius * (s/(S+1.0f) * scale_samples); // (1to4)/(4+1) = (.2, .4, .6, .8) * scale_samples

      lens_lt_sample_aperture(target, aperture, sensor, out, camera->lambda, camera);

      if(sensor(2+k) > 0){
        offset += sensor(k)/sensor(2+k);
        printf("\t[LENTIL] raytraced sensor shift at aperture[%f, %f]: %f", aperture(0), aperture(1), sensor(k)/sensor(2+k));
        count ++;
      }
    }
  }

  // average guesses
  offset /= count; 
  
  // the focus plane/sensor offset:
  // negative because of reverse direction
  if(offset == offset){ // check NaN cases
    const float limit = 45.0f;
    if(offset > limit){
      printf("[LENTIL] sensor offset bigger than maxlimit: %f > %f", offset, limit);
      return limit;
    } else if(offset < -limit){
      printf("[LENTIL] sensor offset smaller than minlimit: %f < %f", offset, -limit);
      return -limit;
    } else {
      return offset; // in mm
    }
  }
}



// returns sensor offset in mm
float camera_set_focus_infinity(Camera *camera)
{
	float parallel_ray_height = camera->lens_aperture_housing_radius * 0.1;
  const Eigen::Vector3f target(0.0, parallel_ray_height, AI_BIG);
  Eigen::VectorXf sensor(5); sensor.setZero();
  Eigen::VectorXf out(5); out.setZero();
  sensor[4] = camera->lambda;
  float offset = 0.0f;
  int count = 0;

  // just point through center of aperture
  Eigen::Vector2f aperture(0, parallel_ray_height);

  const int S = 4;

  // trace a couple of adjoint rays from there to the sensor and
  // see where we need to put the sensor plane.
  for(int s=1; s<=S; s++){
    for(int k=0; k<2; k++){
      
      // reset aperture
      aperture(0) = 0.0f;
      aperture(1) = parallel_ray_height;

      lens_lt_sample_aperture(target, aperture, sensor, out, camera->lambda, camera);

      if(sensor(2+k) > 0){
        offset += sensor(k)/sensor(2+k);
        count ++;
      }
    }
  }

  offset /= count; 
  
  // check NaN cases
  if(offset == offset){
  return offset;
  }
}


std::vector<float> logarithmic_values()
{
  float min = 0.0;
  float max = 45.0;
  float exponent = 2.0; // sharpness
  std::vector<float> log;

  for(float i = -1.0; i <= 1.0; i += 0.0001) {
    log.push_back((i < 0 ? -1 : 1) * std::pow(i, exponent) * (max - min) + min);
  }

  return log;
}


// line plane intersection with fixed intersection at y = 0
// used for finding the focal length and sensor shift
Eigen::Vector3f line_plane_intersection(Eigen::Vector3f rayOrigin, Eigen::Vector3f rayDirection)
{
  Eigen::Vector3f coord(100.0, 0.0, 100.0);
  Eigen::Vector3f planeNormal(0.0, 1.0, 0.0);
  rayDirection.normalize();
  coord.normalize();
  return rayOrigin + (rayDirection * (coord.dot(planeNormal) - planeNormal.dot(rayOrigin)) / planeNormal.dot(rayDirection));
}


float camera_get_y0_intersection_distance(float sensor_shift, float intersection_distance, Camera *camera)
{
  Eigen::VectorXf sensor(5); sensor.setZero();
  Eigen::VectorXf aperture(5); aperture.setZero();
  Eigen::VectorXf out(5); out.setZero();
  sensor(4) = camera->lambda;
  aperture(1) = camera->lens_aperture_housing_radius * 0.25;

  lens_pt_sample_aperture(sensor, aperture, sensor_shift, camera);

  sensor(0) += sensor(2) * sensor_shift;
	sensor(1) += sensor(3) * sensor_shift;

	float transmittance = lens_evaluate(sensor, out, camera);

	// convert from sphere/sphere space to camera space
  Eigen::Vector2f outpos(out(0), out(1));
  Eigen::Vector2f outdir(out(2), out(3));
	Eigen::Vector3f camera_space_pos(0,0,0);
	Eigen::Vector3f camera_space_omega(0,0,0);
  if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, camera_space_pos, camera_space_omega, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
	else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, camera_space_pos, camera_space_omega, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
  else sphereToCs(outpos, outdir, camera_space_pos, camera_space_omega, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
  
  return line_plane_intersection(camera_space_pos, camera_space_omega)(2);
}


// focal_distance is in mm
float logarithmic_focus_search(const float focal_distance, Camera *camera){
  float closest_distance = 999999999.0f;
  float best_sensor_shift = 0.0f;
  for (float sensorshift : logarithmic_values()){
  	float intersection_distance = 0.0f;
    intersection_distance = camera_get_y0_intersection_distance(sensorshift, intersection_distance, camera);
    float new_distance = focal_distance - intersection_distance;

    if (new_distance < closest_distance && new_distance > 0.0f){
      closest_distance = new_distance;
      best_sensor_shift = sensorshift;
    }
  }

  return best_sensor_shift;
}



inline bool trace_ray_focus_check(float sensor_shift, float &test_focus_distance, Camera *camera)
{
  Eigen::VectorXf sensor(5); sensor.setZero();
  Eigen::VectorXf aperture(5); aperture.setZero();
  Eigen::VectorXf out(5); out.setZero();
  sensor(4) = camera->lambda;
  aperture(1) = camera->lens_aperture_housing_radius * 0.25;

	lens_pt_sample_aperture(sensor, aperture, sensor_shift, camera);

  // move to beginning of polynomial
	sensor(0) += sensor(2) * sensor_shift;
	sensor(1) += sensor(3) * sensor_shift;

	// propagate ray from sensor to outer lens element
  float transmittance = lens_evaluate(sensor, out, camera);
  if(transmittance <= 0.0f) return false;

  // crop out by outgoing pupil
  if( out(0)*out(0) + out(1)*out(1) > camera->lens_outer_pupil_radius*camera->lens_outer_pupil_radius){
    return false;
  }

  // crop at inward facing pupil
  const float px = sensor(0) + sensor(2) * camera->lens_back_focal_length;
  const float py = sensor(1) + sensor(3) * camera->lens_back_focal_length;
  if (px*px + py*py > camera->lens_inner_pupil_radius*camera->lens_inner_pupil_radius){
    return false;
  }

	// convert from sphere/sphere space to camera space
  Eigen::Vector2f outpos(out(0), out(1));
  Eigen::Vector2f outdir(out(2), out(3));
	Eigen::Vector3f camera_space_pos(0,0,0);
	Eigen::Vector3f camera_space_omega(0,0,0);
  if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, camera_space_pos, camera_space_omega, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
	else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, camera_space_pos, camera_space_omega, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
  else sphereToCs(outpos, outdir, camera_space_pos, camera_space_omega, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);

  test_focus_distance = line_plane_intersection(camera_space_pos, camera_space_omega)(2);
  return true;
}





inline void trace_ray(bool original_ray, 
                      int &tries, 
                      const float input_sx, const float input_sy, 
                      const float input_lensx, const float input_lensy, 
                      float &r1, float &r2, 
                      Eigen::Vector3f &weight, 
                      Eigen::Vector3f &origin, 
                      Eigen::Vector3f &direction, 
                      Camera *camera)
{

  tries = 0;
  bool ray_succes = false;

  Eigen::VectorXf sensor(5); sensor.setZero();
  Eigen::VectorXf aperture(5); aperture.setZero();
  Eigen::VectorXf out(5); out.setZero();

  while(ray_succes == false && tries <= camera->vignetting_retries){

  	// set sensor position coords
	  sensor(0) = input_sx * (camera->sensor_width * 0.5f);
	  sensor(1) = input_sy * (camera->sensor_width * 0.5f);
  	sensor(2) = sensor(3) = 0.0f;
	  sensor(4) = camera->lambda;
    // tmp debug
    // sensor(0) = 0.0f;
    // sensor(1) = 0.0f;

    aperture.setZero();
    out.setZero();

	  // no dof, all rays through single aperture point
	  if (!camera->dof) aperture(0) = aperture(1) = 0.0;
	  else if (camera->dof && camera->aperture_blades <= 2) {
			// transform unit square to unit disk
		  Eigen::Vector2d unit_disk(0.0f, 0.0f);
		  if (tries == 0) concentric_disk_sample(input_lensx, input_lensy, unit_disk, false);
		  else {
		  	if (original_ray) {
				  r1 = xor128() / 4294967296.0f;
				  r2 = xor128() / 4294967296.0f;
			  }

		  	concentric_disk_sample(r1, r2, unit_disk, true);
		  }

      aperture(0) = unit_disk(0) * camera->aperture_radius;
      aperture(1) = unit_disk(1) * camera->aperture_radius;
	  } 
	  else if (camera->dof && camera->aperture_blades > 2) {
	  	if (tries == 0) lens_sample_aperture(aperture(0), aperture(1), input_lensx, input_lensy, camera->aperture_radius, camera->aperture_blades);
	  	else {
	  		if (original_ray) {
		  		r1 = xor128() / 4294967296.0f;
		  		r2 = xor128() / 4294967296.0f;
	  		}

	  		lens_sample_aperture(aperture(0), aperture(1), r1, r2, camera->aperture_radius, camera->aperture_blades);
	  	}
	  }

	  if (camera->dof) {
	  	// aperture sampling, to make sure ray is able to propagate through whole lens system
	  	lens_pt_sample_aperture(sensor, aperture, camera->sensor_shift, camera);
	  }

    //printf("[%f, %f, %f],", aperture(0), aperture(1), -camera->lens_aperture_pos);
	  

	  // move to beginning of polynomial
		sensor(0) += sensor(2) * camera->sensor_shift;
		sensor(1) += sensor(3) * camera->sensor_shift;


		// propagate ray from sensor to outer lens element
	  float transmittance = lens_evaluate(sensor, out, camera);
		if(transmittance <= 0.0f) {
			++tries;
			continue;
		}


		// crop out by outgoing pupil
		if( out(0)*out(0) + out(1)*out(1) > camera->lens_outer_pupil_radius*camera->lens_outer_pupil_radius){
			++tries;
			continue;
		}


		// crop at inward facing pupil
		const float px = sensor(0) + sensor(2) * camera->lens_back_focal_length;
		const float py = sensor(1) + sensor(3) * camera->lens_back_focal_length; //(note that lens_back_focal_length is the back focal length, i.e. the distance unshifted sensor -> pupil)
		if (px*px + py*py > camera->lens_inner_pupil_radius*camera->lens_inner_pupil_radius) {
			++tries;
			continue;
		}
		
		ray_succes = true;
	}

	if (ray_succes == false) weight << 0.0, 0.0, 0.0;


	// convert from sphere/sphere space to camera space
  Eigen::Vector2f outpos(out[0], out[1]);
  Eigen::Vector2f outdir(out[2], out[3]);
  Eigen::Vector3f cs_origin(0,0,0);
  Eigen::Vector3f cs_direction(0,0,0);
  if (camera->lens_outer_pupil_geometry == "cyl-y") cylinderToCs(outpos, outdir, cs_origin, cs_direction, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, true);
	else if (camera->lens_outer_pupil_geometry == "cyl-x") cylinderToCs(outpos, outdir, cs_origin, cs_direction, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius, false);
  else sphereToCs(outpos, outdir, cs_origin, cs_direction, -camera->lens_outer_pupil_curvature_radius, camera->lens_outer_pupil_curvature_radius);
  
  origin = cs_origin;
  direction = cs_direction;

  //printf("[%f,%f,%f],", origin[0], origin[1], origin[2]);


  switch (camera->unitModel){
    case mm:
    {
      origin *= -1.0; // reverse rays and convert to cm
      direction *= -1.0; //reverse rays and convert to cm
    } break;
    case cm:
    { 
      origin *= -0.1; // reverse rays and convert to cm
      direction *= -0.1; //reverse rays and convert to cm
    } break;
    case dm:
    {
      origin *= -0.01; // reverse rays and convert to cm
      direction *= -0.01; //reverse rays and convert to cm
    } break;
    case m:
    {
      origin *= -0.001; // reverse rays and convert to cm
      direction *= -0.001; //reverse rays and convert to cm
    }
  }

  direction.normalize();

  // Nan bailout
  if (origin(0) != origin(0) || origin(1) != origin(1) || origin(2) != origin(2) || 
    direction(0) != direction(0) || direction(1) != direction(1) || direction(2) != direction(2))
  {
    weight.setZero();
  }

}


// given camera space scene point, return point on sensor
inline bool trace_backwards(Eigen::Vector3f target, 
                            const float aperture_radius, 
                            const float lambda, 
                            Eigen::Vector2d &sensor_position, 
                            const float sensor_shift, 
                            Camera *camera)
{
   // initialize 5d light fields
   Eigen::VectorXf sensor(5); sensor << 0,0,0,0, lambda;
   Eigen::VectorXf out(5); out.setZero();
   Eigen::Vector2f aperture(0,0);

   Eigen::Vector2d lens;
   concentric_disk_sample(xor128() / 4294967296.0f, xor128() / 4294967296.0f, lens, true);
   aperture(0) = lens(0) * aperture_radius;
   aperture(1) = lens(1) * aperture_radius;

   if(lens_lt_sample_aperture(target, aperture, sensor, out, lambda, camera) <= 0.0f) return false;

   // crop at inward facing pupil, not needed to crop by outgoing because already done in lens_lt_sample_aperture()
   const float px = sensor(0) + sensor(2) * camera->lens_back_focal_length;
   const float py = sensor(1) + sensor(3) * camera->lens_back_focal_length; //(note that lens_focal_length is the back focal length, i.e. the distance unshifted sensor -> pupil)
   if (px*px + py*py > camera->lens_inner_pupil_radius*camera->lens_inner_pupil_radius) return false;


/*
  Draw &draw = camera->draw;
  // THIS IS NOT THREAD SAFE!! DRAWING CAN ONLY BE RAN ON ONE THREAD
  if (draw.enabled) {
    draw.sensor.push_back(std::vector<float> {sensor[0], sensor[1], sensor[2], sensor[3]});
    draw.aperture.push_back(std::vector<float> {aperture[0], aperture[1], aperture[2], aperture[3]});
    draw.out.push_back(std::vector<float> {out[0], out[1], out[2], out[3]});
    draw.pxpy.push_back(std::vector<float> {px, py});
  }
*/


   // shift sensor
   sensor(0) += sensor(2) * -sensor_shift;
   sensor(1) += sensor(3) * -sensor_shift;
/*
  if (draw.enabled) {
    draw.sensor_shifted.push_back(std::vector<float> {sensor[0], sensor[1]});
  }
*/
   sensor_position(0) = sensor(0);
   sensor_position(1) = sensor(1);

   return true;
}


// note that this is all with an unshifted sensor
void trace_backwards_for_fstop(Camera *camera, const float fstop_target, float &calculated_fstop, float &calculated_aperture_radius)
{
  const int maxrays = 1000;
  float best_valid_fstop = 0.0f;
  float best_valid_aperture_radius = 0.0f;

  for (int i = 1; i < maxrays; i++)
  {
    const float parallel_ray_height = (static_cast<float>(i)/static_cast<float>(maxrays)) * camera->lens_outer_pupil_radius;
    const Eigen::Vector3f target(0, parallel_ray_height, AI_BIG);
    Eigen::VectorXf sensor(5); sensor << 0,0,0,0, camera->lambda;
    Eigen::VectorXf out(5); out.setZero();

    // just point through center of aperture
    Eigen::Vector2f aperture(0.01f, parallel_ray_height);

    if(lens_lt_sample_aperture(target, aperture, sensor, out, camera->lambda, camera) <= 0.0f) continue;

    // crop at inner pupil
    const float px = sensor(0) + (sensor(2) * camera->lens_back_focal_length);
    const float py = sensor(1) + (sensor(3) * camera->lens_back_focal_length);
    if (px*px + py*py > camera->lens_inner_pupil_radius*camera->lens_inner_pupil_radius) continue;

    // somehow need to get last vertex positiondata.. don't think what i currently have is correct
    Eigen::Vector3f out_cs_pos(0,0,0);
    Eigen::Vector3f out_cs_dir(0,0,0);
    Eigen::Vector2f outpos(out(0), out(1));
    Eigen::Vector2f outdir(out(2), out(3)); 
    if (camera->lens_inner_pupil_geometry == "cyl-y") {
      cylinderToCs(outpos, outdir, out_cs_pos, out_cs_dir, - camera->lens_inner_pupil_curvature_radius + camera->lens_back_focal_length, camera->lens_inner_pupil_curvature_radius, true);
    }
    else if (camera->lens_inner_pupil_geometry == "cyl-x") {
      cylinderToCs(outpos, outdir, out_cs_pos, out_cs_dir, - camera->lens_inner_pupil_curvature_radius + camera->lens_back_focal_length, camera->lens_inner_pupil_curvature_radius, false);
    }
    else sphereToCs(outpos, outdir, out_cs_pos, out_cs_dir, - camera->lens_inner_pupil_curvature_radius + camera->lens_back_focal_length, camera->lens_inner_pupil_curvature_radius);

    const float theta = std::atan(out_cs_pos(1) / out_cs_pos(2));
    const float fstop = 1.0 / (std::sin(theta)* 2.0);

    if (fstop < fstop_target) {
      calculated_fstop = best_valid_fstop;
      calculated_aperture_radius = best_valid_aperture_radius;
      break;
    } else {
      best_valid_fstop = fstop;
      best_valid_aperture_radius = parallel_ray_height;
    }
  }
}
