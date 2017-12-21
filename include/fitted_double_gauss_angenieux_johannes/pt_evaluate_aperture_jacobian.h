const float dx00 =  + 0.224951  + -0.144064 *lens_ipow(dy, 2) + -0.169814 *lens_ipow(dx, 2) + 0.000691894 *y*dy + -0.000323112 *lens_ipow(y, 2) + 0.00394849 *x*dx + -0.00132702 *lens_ipow(x, 2) + 0.142358 *lens_ipow(lambda, 3) + -2.03405e-05 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -7.21627e-07 *lens_ipow(y, 4) + -0.0457488 *x*dx*lens_ipow(dy, 2) + -0.00120826 *x*y*dx*dy + -3.28152e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + 0.626383 *lens_ipow(dy, 6) + 9.92971e-05 *lens_ipow(y, 3)*lens_ipow(dx, 2)*dy + -0.000219348 *lens_ipow(x, 2)*y*lens_ipow(dy, 3) + 0.000538722 *lens_ipow(x, 2)*y*lens_ipow(dx, 2)*dy + 1.44099e-07 *lens_ipow(x, 5)*dx + -9.05611e-08 *lens_ipow(x, 4)*lens_ipow(y, 2)*lens_ipow(dx, 2) + -3.2374e-11 *lens_ipow(x, 8) + 8.79781e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(lambda, 5) + 3.57871e-06 *lens_ipow(x, 4)*lens_ipow(lambda, 5) + -0.90552 *lens_ipow(lambda, 10) + -6.86393e-10 *lens_ipow(x, 6)*lens_ipow(y, 2)*lens_ipow(dy, 2) + -4.83617e-13 *lens_ipow(x, 6)*lens_ipow(y, 4)+0.0f;
const float dx01 =  + 3.05366e-05  + -0.0193266 *dx*dy + 0.0035403 *y*dx + 0.000691894 *x*dy + -0.000646224 *x*y + 0.0273893 *y*dx*lens_ipow(dy, 2) + -0.027822 *y*lens_ipow(dx, 3) + -4.0681e-05 *x*y*lens_ipow(dx, 2) + -2.88651e-06 *x*lens_ipow(y, 3) + -0.000604129 *lens_ipow(x, 2)*dx*dy + -2.18768e-06 *lens_ipow(x, 3)*y + -0.825887 *lens_ipow(dx, 5)*dy + 0.000297891 *x*lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + -7.31161e-05 *lens_ipow(x, 3)*lens_ipow(dy, 3) + 0.000179574 *lens_ipow(x, 3)*lens_ipow(dx, 2)*dy + -3.62244e-08 *lens_ipow(x, 5)*y*lens_ipow(dx, 2) + 5.86521e-06 *lens_ipow(x, 3)*y*lens_ipow(lambda, 5) + 0.833187 *y*lens_ipow(dx, 9) + -1.96112e-10 *lens_ipow(x, 7)*y*lens_ipow(dy, 2) + -2.76353e-13 *lens_ipow(x, 7)*lens_ipow(y, 3)+0.0f;
const float dx02 =  + 28.4765  + -15.2543 *lens_ipow(dy, 2) + -44.2829 *lens_ipow(dx, 2) + -0.0193266 *y*dy + 0.00177015 *lens_ipow(y, 2) + -0.339628 *x*dx + 0.00197425 *lens_ipow(x, 2) + 5.00587 *lens_ipow(lambda, 4) + 0.0136947 *lens_ipow(y, 2)*lens_ipow(dy, 2) + -0.041733 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -4.0681e-05 *x*lens_ipow(y, 2)*dx + -0.0228744 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -0.000604129 *lens_ipow(x, 2)*y*dy + 18.3921 *lens_ipow(dy, 6) + 134.58 *lens_ipow(dx, 4)*lens_ipow(dy, 2) + -4.12944 *y*lens_ipow(dx, 4)*dy + 0.000198594 *x*lens_ipow(y, 3)*dx*dy + 0.000359148 *lens_ipow(x, 3)*y*dx*dy + 2.40165e-08 *lens_ipow(x, 6) + -3.62244e-08 *lens_ipow(x, 5)*lens_ipow(y, 2)*dx + -24.5286 *lens_ipow(lambda, 10) + 3.74934 *lens_ipow(y, 2)*lens_ipow(dx, 8)+0.0f;
const float dx03 =  + -30.5087 *dx*dy + -0.0193266 *y*dx + -0.288129 *x*dy + 0.000691894 *x*y + 0.0273893 *lens_ipow(y, 2)*dx*dy + -0.0457488 *lens_ipow(x, 2)*dx*dy + -0.000604129 *lens_ipow(x, 2)*y*dx + 110.353 *dx*lens_ipow(dy, 5) + 53.832 *lens_ipow(dx, 5)*dy + -0.825887 *y*lens_ipow(dx, 5) + 3.7583 *x*lens_ipow(dy, 5) + 9.92971e-05 *x*lens_ipow(y, 3)*lens_ipow(dx, 2) + -0.000219348 *lens_ipow(x, 3)*y*lens_ipow(dy, 2) + 0.000179574 *lens_ipow(x, 3)*y*lens_ipow(dx, 2) + -1.96112e-10 *lens_ipow(x, 7)*lens_ipow(y, 2)*dy+0.0f;
const float dx04 =  + 0.427074 *x*lens_ipow(lambda, 2) + 20.0235 *dx*lens_ipow(lambda, 3) + 1.4663e-05 *lens_ipow(x, 3)*lens_ipow(y, 2)*lens_ipow(lambda, 4) + 3.57871e-06 *lens_ipow(x, 5)*lens_ipow(lambda, 4) + -245.286 *dx*lens_ipow(lambda, 9) + -9.0552 *x*lens_ipow(lambda, 9)+0.0f;
const float dx10 =  + -0.0318128 *dx*dy + 0.00030524 *y*dx + 0.00276749 *x*dy + -0.000564642 *x*y + 0.0277696 *y*dx*lens_ipow(dy, 2) + -0.0151957 *x*lens_ipow(dy, 3) + 0.0202759 *x*lens_ipow(dx, 2)*dy + -0.000272901 *x*y*lens_ipow(dy, 2) + -0.00079316 *x*y*lens_ipow(dx, 2) + -2.91624e-06 *x*lens_ipow(y, 3) + -3.05404e-06 *lens_ipow(x, 3)*y + -0.0554697 *y*lens_ipow(dx, 5) + -1.07264e-05 *lens_ipow(x, 2)*lens_ipow(y, 2)*dx*dy + 8.97577e-07 *lens_ipow(y, 5)*dx*lens_ipow(dy, 2) + 5.80718e-06 *x*lens_ipow(y, 3)*lens_ipow(lambda, 5) + -1.80449e-11 *x*lens_ipow(y, 7)*lens_ipow(dx, 2) + 1.66699e-12 *x*lens_ipow(y, 8)*dy + -1.85691e-13 *lens_ipow(x, 3)*lens_ipow(y, 7)+0.0f;
const float dx11 =  + 0.218098  + -0.132441 *lens_ipow(dy, 2) + -0.11828 *lens_ipow(dx, 2) + 0.0038954 *y*dy + -0.000857569 *lens_ipow(y, 2) + 0.00030524 *x*dx + -0.000282321 *lens_ipow(x, 2) + 0.138184 *lens_ipow(lambda, 3) + -0.0246573 *y*lens_ipow(dx, 2)*dy + -0.00145422 *lens_ipow(y, 2)*lens_ipow(dy, 2) + -0.000218467 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -3.84866e-06 *lens_ipow(y, 4) + 0.0277696 *x*dx*lens_ipow(dy, 2) + -0.000136451 *lens_ipow(x, 2)*lens_ipow(dy, 2) + -0.00039658 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -4.37436e-06 *lens_ipow(x, 2)*lens_ipow(y, 2) + -7.63511e-07 *lens_ipow(x, 4) + 2.29255 *lens_ipow(dx, 4)*lens_ipow(dy, 2) + -0.0554697 *x*lens_ipow(dx, 5) + -7.1509e-06 *lens_ipow(x, 3)*y*dx*dy + 2.90011e-06 *lens_ipow(y, 4)*lens_ipow(lambda, 4) + -4.8873e-07 *lens_ipow(y, 5)*lens_ipow(dx, 2)*dy + 4.48789e-06 *x*lens_ipow(y, 4)*dx*lens_ipow(dy, 2) + 8.71077e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(lambda, 5) + -0.868843 *lens_ipow(lambda, 10) + -6.31573e-11 *lens_ipow(x, 2)*lens_ipow(y, 6)*lens_ipow(dx, 2) + 6.66798e-12 *lens_ipow(x, 2)*lens_ipow(y, 7)*dy + -3.24959e-13 *lens_ipow(x, 4)*lens_ipow(y, 6)+0.0f;
const float dx12 =  + -29.9736 *dx*dy + -0.236561 *y*dx + -0.0318128 *x*dy + 0.00030524 *x*y + -0.0246573 *lens_ipow(y, 2)*dx*dy + -0.000145644 *lens_ipow(y, 3)*dx + 0.0277696 *x*y*lens_ipow(dy, 2) + 0.0202759 *lens_ipow(x, 2)*dx*dy + -0.00079316 *lens_ipow(x, 2)*y*dx + 9.17021 *y*lens_ipow(dx, 3)*lens_ipow(dy, 2) + -0.277349 *x*y*lens_ipow(dx, 4) + -3.57545e-06 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy + 1892.72 *lens_ipow(dx, 3)*lens_ipow(dy, 5) + -1.6291e-07 *lens_ipow(y, 6)*dx*dy + 8.97577e-07 *x*lens_ipow(y, 5)*lens_ipow(dy, 2) + -1.80449e-11 *lens_ipow(x, 2)*lens_ipow(y, 7)*dx+0.0f;
const float dx13 =  + 28.51  + -45.5979 *lens_ipow(dy, 2) + -14.9868 *lens_ipow(dx, 2) + -0.264882 *y*dy + 0.0019477 *lens_ipow(y, 2) + -0.0318128 *x*dx + 0.00138375 *lens_ipow(x, 2) + 4.95146 *lens_ipow(lambda, 4) + -0.0123286 *lens_ipow(y, 2)*lens_ipow(dx, 2) + -0.000969477 *lens_ipow(y, 3)*dy + 0.0555393 *x*y*dx*dy + -0.0227936 *lens_ipow(x, 2)*lens_ipow(dy, 2) + 0.010138 *lens_ipow(x, 2)*lens_ipow(dx, 2) + -0.000272901 *lens_ipow(x, 2)*y*dy + 4.5851 *y*lens_ipow(dx, 4)*dy + -3.57545e-06 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx + 311.29 *lens_ipow(dy, 8) + 2365.9 *lens_ipow(dx, 4)*lens_ipow(dy, 4) + -8.14549e-08 *lens_ipow(y, 6)*lens_ipow(dx, 2) + 1.79515e-06 *x*lens_ipow(y, 5)*dx*dy + -24.1952 *lens_ipow(lambda, 10) + 8.33497e-13 *lens_ipow(x, 2)*lens_ipow(y, 8)+0.0f;
const float dx14 =  + 0.414553 *y*lens_ipow(lambda, 2) + 19.8058 *dy*lens_ipow(lambda, 3) + 2.32009e-06 *lens_ipow(y, 5)*lens_ipow(lambda, 3) + 1.4518e-05 *lens_ipow(x, 2)*lens_ipow(y, 3)*lens_ipow(lambda, 4) + -241.952 *dy*lens_ipow(lambda, 9) + -8.68843 *y*lens_ipow(lambda, 9)+0.0f;
const float dx20 =  + -0.0317262  + -0.0108622 *lens_ipow(dy, 2) + -0.0313598 *lens_ipow(dx, 2) + 0.000269457 *y*dy + 3.19298e-06 *y*dx + -2.94324e-05 *lens_ipow(y, 2) + 0.000584191 *x*dx + -8.55835e-05 *lens_ipow(x, 2) + 0.00776112 *lens_ipow(lambda, 3) + -0.00175831 *y*lens_ipow(dy, 5) + 2.3999e-08 *x*lens_ipow(y, 4)*dx + 6.4401e-05 *lens_ipow(x, 2)*lens_ipow(dy, 4) + -9.9385e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dy, 2) + 2.37188e-08 *lens_ipow(x, 4)*y*dy + 3.72482e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(lambda, 3) + 4.36318e-08 *lens_ipow(y, 4)*lens_ipow(lambda, 4) + -9.31642e-07 *lens_ipow(y, 4)*lens_ipow(dx, 4) + 2.99453e-11 *lens_ipow(y, 7)*dy + 5.87613e-07 *lens_ipow(x, 2)*lens_ipow(y, 3)*lens_ipow(dx, 2)*dy + 2.29914e-07 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx*lens_ipow(dy, 2) + 2.49982e-07 *lens_ipow(x, 4)*lens_ipow(lambda, 4) + -2.15337e-08 *lens_ipow(x, 4)*lens_ipow(y, 2)*lens_ipow(dx, 2) + -1.08498e-11 *lens_ipow(x, 4)*lens_ipow(y, 4) + -2.18055e-09 *lens_ipow(x, 6)*lens_ipow(dy, 2) + 1.58097e-10 *lens_ipow(x, 7)*dx + -1.50152e-12 *lens_ipow(x, 8) + -5.0278e-06 *lens_ipow(x, 3)*dx*lens_ipow(lambda, 5) + -0.0538191 *lens_ipow(lambda, 10) + -9.12368e-15 *lens_ipow(x, 2)*lens_ipow(y, 8) + 1.27577e-06 *lens_ipow(x, 5)*lens_ipow(dx, 5) + -2.17607e-14 *lens_ipow(x, 8)*lens_ipow(y, 2)+0.0f;
const float dx21 =  + -0.0201563 *dx*dy + -4.66327e-05 *y*dx + 0.000269457 *x*dy + 3.19298e-06 *x*dx + -5.88648e-05 *x*y + -0.0639609 *lens_ipow(dx, 5)*dy + -0.000736957 *lens_ipow(y, 2)*dx*lens_ipow(dy, 3) + -0.00175831 *x*lens_ipow(dy, 5) + 4.7998e-08 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx + -6.62566e-07 *lens_ipow(x, 3)*y*lens_ipow(dy, 2) + 4.74377e-09 *lens_ipow(x, 5)*dy + 2.48321e-07 *lens_ipow(x, 3)*y*lens_ipow(lambda, 3) + 4.27462e-11 *lens_ipow(y, 7)*dx + 1.74527e-07 *x*lens_ipow(y, 3)*lens_ipow(lambda, 4) + -3.72657e-06 *x*lens_ipow(y, 3)*lens_ipow(dx, 4) + 2.09617e-10 *x*lens_ipow(y, 6)*dy + 5.87613e-07 *lens_ipow(x, 3)*lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + 1.14957e-07 *lens_ipow(x, 4)*y*dx*lens_ipow(dy, 2) + -8.61349e-09 *lens_ipow(x, 5)*y*lens_ipow(dx, 2) + -8.67988e-12 *lens_ipow(x, 5)*lens_ipow(y, 3) + -2.43298e-14 *lens_ipow(x, 3)*lens_ipow(y, 7) + -4.83571e-15 *lens_ipow(x, 9)*y+0.0f;
const float dx22 =  + 0.398331  + -0.498095 *lens_ipow(dy, 2) + -1.46932 *lens_ipow(dx, 2) + -0.0201563 *y*dy + -2.33164e-05 *lens_ipow(y, 2) + -0.0627196 *x*dx + 3.19298e-06 *x*y + 0.000292095 *lens_ipow(x, 2) + -0.319805 *y*lens_ipow(dx, 4)*dy + -0.000245652 *lens_ipow(y, 3)*lens_ipow(dy, 3) + 1.19995e-08 *lens_ipow(x, 2)*lens_ipow(y, 4) + 5.34328e-12 *lens_ipow(y, 8) + -3.72657e-06 *x*lens_ipow(y, 4)*lens_ipow(dx, 3) + 3.91742e-07 *lens_ipow(x, 3)*lens_ipow(y, 3)*dx*dy + 5.74784e-08 *lens_ipow(x, 4)*lens_ipow(y, 2)*lens_ipow(dy, 2) + -8.61349e-09 *lens_ipow(x, 5)*lens_ipow(y, 2)*dx + 1.97621e-11 *lens_ipow(x, 8) + -1.25695e-06 *lens_ipow(x, 4)*lens_ipow(lambda, 5) + 1.06314e-06 *lens_ipow(x, 6)*lens_ipow(dx, 4)+0.0f;
const float dx23 =  + -0.996191 *dx*dy + -0.0201563 *y*dx + -0.0217244 *x*dy + 0.000269457 *x*y + -0.0639609 *y*lens_ipow(dx, 5) + -0.000736957 *lens_ipow(y, 3)*dx*lens_ipow(dy, 2) + -0.00879156 *x*y*lens_ipow(dy, 4) + 8.5868e-05 *lens_ipow(x, 3)*lens_ipow(dy, 3) + -6.62566e-07 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy + 4.74377e-09 *lens_ipow(x, 5)*y + 2.99453e-11 *x*lens_ipow(y, 7) + 1.95871e-07 *lens_ipow(x, 3)*lens_ipow(y, 3)*lens_ipow(dx, 2) + 1.14957e-07 *lens_ipow(x, 4)*lens_ipow(y, 2)*dx*dy + -6.23015e-10 *lens_ipow(x, 7)*dy+0.0f;
const float dx24 =  + 0.0232834 *x*lens_ipow(lambda, 2) + 3.72482e-07 *lens_ipow(x, 3)*lens_ipow(y, 2)*lens_ipow(lambda, 2) + 1.74527e-07 *x*lens_ipow(y, 4)*lens_ipow(lambda, 3) + 1.99986e-07 *lens_ipow(x, 5)*lens_ipow(lambda, 3) + -6.28475e-06 *lens_ipow(x, 4)*dx*lens_ipow(lambda, 4) + -0.538191 *x*lens_ipow(lambda, 9)+0.0f;
const float dx30 =  + -0.019758 *dx*dy + 0.000239951 *y*dx + 4.27294e-07 *x*dy + -4.95779e-05 *x*y + 0.0014548 *y*dx*lens_ipow(dy, 2) + -1.0073e-07 *lens_ipow(y, 4)*dx*dy + -0.000240397 *x*dy*lens_ipow(lambda, 4) + 0.0101079 *x*lens_ipow(dx, 4)*dy + -1.52259e-06 *x*lens_ipow(y, 3)*lens_ipow(dy, 2) + -8.93305e-10 *x*lens_ipow(y, 5) + 4.02911e-08 *lens_ipow(x, 2)*lens_ipow(y, 3)*dx + -7.63395e-07 *lens_ipow(x, 3)*y*lens_ipow(dx, 2) + 4.29674e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*dy + -5.47339e-07 *lens_ipow(x, 4)*dx*dy + -7.43747e-10 *lens_ipow(x, 5)*y + 3.32197e-07 *x*lens_ipow(y, 3)*lens_ipow(lambda, 3) + 1.15092e-07 *x*lens_ipow(y, 4)*lens_ipow(dx, 2)*dy + 4.01596e-08 *lens_ipow(x, 5)*lens_ipow(dy, 3) + 3.12848e-14 *lens_ipow(y, 9)*dx + -3.20805e-14 *lens_ipow(x, 5)*lens_ipow(y, 5)+0.0f;
const float dx31 =  + -0.0318898  + -0.0308361 *lens_ipow(dy, 2) + -0.0111372 *lens_ipow(dx, 2) + 0.000563409 *y*dy + -8.06045e-05 *lens_ipow(y, 2) + 0.000239951 *x*dx + -2.47889e-05 *lens_ipow(x, 2) + 0.00769775 *lens_ipow(lambda, 3) + 0.0014548 *x*dx*lens_ipow(dy, 2) + 0.0825935 *lens_ipow(dx, 4)*lens_ipow(dy, 2) + -4.02919e-07 *x*lens_ipow(y, 3)*dx*dy + -2.28389e-06 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dy, 2) + -2.23326e-09 *lens_ipow(x, 2)*lens_ipow(y, 4) + 4.02911e-08 *lens_ipow(x, 3)*lens_ipow(y, 2)*dx + -1.90849e-07 *lens_ipow(x, 4)*lens_ipow(dx, 2) + 2.14837e-08 *lens_ipow(x, 4)*y*dy + -1.23958e-10 *lens_ipow(x, 6) + 4.98295e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(lambda, 3) + 0.0597839 *lens_ipow(dx, 8) + -2.69817e-09 *lens_ipow(y, 6)*lens_ipow(dx, 2) + 1.74686e-10 *lens_ipow(y, 7)*dy + -1.67714e-12 *lens_ipow(y, 8) + 2.30184e-07 *lens_ipow(x, 2)*lens_ipow(y, 3)*lens_ipow(dx, 2)*dy + -5.31305e-06 *lens_ipow(y, 3)*dy*lens_ipow(lambda, 5) + -0.0510612 *lens_ipow(lambda, 10) + 1.49911e-06 *lens_ipow(y, 5)*lens_ipow(dy, 5) + 1.24063e-09 *lens_ipow(y, 6)*lens_ipow(lambda, 4) + 2.81563e-13 *x*lens_ipow(y, 8)*dx + -2.67337e-14 *lens_ipow(x, 6)*lens_ipow(y, 4)+0.0f;
const float dx32 =  + -1.01457 *dx*dy + -0.0222744 *y*dx + -0.019758 *x*dy + 0.000239951 *x*y + 0.0014548 *x*y*lens_ipow(dy, 2) + 3.89494 *dx*lens_ipow(dy, 5) + 0.330374 *y*lens_ipow(dx, 3)*lens_ipow(dy, 2) + -1.0073e-07 *x*lens_ipow(y, 4)*dy + 0.0202159 *lens_ipow(x, 2)*lens_ipow(dx, 3)*dy + 1.34304e-08 *lens_ipow(x, 3)*lens_ipow(y, 3) + -3.81697e-07 *lens_ipow(x, 4)*y*dx + -1.09468e-07 *lens_ipow(x, 5)*dy + 0.478271 *y*lens_ipow(dx, 7) + -7.70905e-10 *lens_ipow(y, 7)*dx + 1.15092e-07 *lens_ipow(x, 2)*lens_ipow(y, 4)*dx*dy + 3.12848e-14 *x*lens_ipow(y, 9)+0.0f;
const float dx33 =  + 0.400049  + -1.5353 *lens_ipow(dy, 2) + -0.507283 *lens_ipow(dx, 2) + -0.0616722 *y*dy + 0.000281705 *lens_ipow(y, 2) + -0.019758 *x*dx + 2.13647e-07 *lens_ipow(x, 2) + 0.0029096 *x*y*dx*dy + 9.73735 *lens_ipow(dx, 2)*lens_ipow(dy, 4) + 0.165187 *y*lens_ipow(dx, 4)*dy + -1.0073e-07 *x*lens_ipow(y, 4)*dx + -0.000120199 *lens_ipow(x, 2)*lens_ipow(lambda, 4) + 0.00505397 *lens_ipow(x, 2)*lens_ipow(dx, 4) + -1.52259e-06 *lens_ipow(x, 2)*lens_ipow(y, 3)*dy + 1.07419e-08 *lens_ipow(x, 4)*lens_ipow(y, 2) + -1.09468e-07 *lens_ipow(x, 5)*dx + 2.18357e-11 *lens_ipow(y, 8) + 5.7546e-08 *lens_ipow(x, 2)*lens_ipow(y, 4)*lens_ipow(dx, 2) + 2.00798e-08 *lens_ipow(x, 6)*lens_ipow(dy, 2) + -1.32826e-06 *lens_ipow(y, 4)*lens_ipow(lambda, 5) + 46.4022 *lens_ipow(dy, 10) + 1.24926e-06 *lens_ipow(y, 6)*lens_ipow(dy, 4)+0.0f;
const float dx34 =  + 0.0230933 *y*lens_ipow(lambda, 2) + -0.000480794 *lens_ipow(x, 2)*dy*lens_ipow(lambda, 3) + 4.98295e-07 *lens_ipow(x, 2)*lens_ipow(y, 3)*lens_ipow(lambda, 2) + -6.64131e-06 *lens_ipow(y, 4)*dy*lens_ipow(lambda, 4) + -0.510612 *y*lens_ipow(lambda, 9) + 7.08932e-10 *lens_ipow(y, 7)*lens_ipow(lambda, 3)+0.0f;
const float dx40 =  + -1.30378e-07  + -0.000257752 *dx + -7.85651e-06 *x + 0.00357254 *dx*lens_ipow(dy, 2) + 0.00399831 *lens_ipow(dx, 3) + -6.29131e-05 *y*dx*dy + 2.49687e-05 *lens_ipow(y, 2)*lens_ipow(dx, 3) + 5.1081e-05 *x*y*lens_ipow(dy, 3) + -1.2728e-09 *x*lens_ipow(y, 4) + 8.24537e-05 *lens_ipow(x, 2)*dx*lens_ipow(dy, 2) + -2.53426e-09 *lens_ipow(x, 3)*lens_ipow(y, 2) + -1.08371e-09 *lens_ipow(x, 5) + 2.8802e-06 *lens_ipow(y, 3)*lens_ipow(dx, 3)*dy + 3.91659e-07 *x*lens_ipow(y, 2)*lens_ipow(lambda, 4) + -1.97928e-05 *x*lens_ipow(y, 2)*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 9.07765e-06 *lens_ipow(x, 2)*y*dx*lens_ipow(dy, 3) + -3.88118e-06 *lens_ipow(x, 3)*lens_ipow(dy, 4) + -1.90092e-05 *lens_ipow(x, 3)*lens_ipow(dx, 4)+0.0f;
const float dx41 =  + -0.000255053 *dy + -7.92368e-06 *y + 0.00389056 *lens_ipow(dy, 3) + 0.00373562 *lens_ipow(dx, 2)*dy + -6.29131e-05 *x*dx*dy + 7.76996e-05 *lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + -1.08699e-09 *lens_ipow(y, 5) + 4.99374e-05 *x*y*lens_ipow(dx, 3) + 2.55405e-05 *lens_ipow(x, 2)*lens_ipow(dy, 3) + -2.54561e-09 *lens_ipow(x, 2)*lens_ipow(y, 3) + -1.26713e-09 *lens_ipow(x, 4)*y + -1.92831e-05 *lens_ipow(y, 3)*lens_ipow(dy, 4) + -4.04269e-06 *lens_ipow(y, 3)*lens_ipow(dx, 4) + 8.64061e-06 *x*lens_ipow(y, 2)*lens_ipow(dx, 3)*dy + 3.91659e-07 *lens_ipow(x, 2)*y*lens_ipow(lambda, 4) + -1.97928e-05 *lens_ipow(x, 2)*y*lens_ipow(dx, 2)*lens_ipow(dy, 2) + 3.02588e-06 *lens_ipow(x, 3)*dx*lens_ipow(dy, 3)+0.0f;
const float dx42 =  + -5.09208e-06  + -0.0387046 *dx + -0.000257752 *x + 0.00747123 *y*dx*dy + 0.00357254 *x*lens_ipow(dy, 2) + 0.0119949 *x*lens_ipow(dx, 2) + -6.29131e-05 *x*y*dy + -3.36611 *dx*lens_ipow(dy, 4) + -6.84799 *lens_ipow(dx, 3)*lens_ipow(dy, 2) + -3.28559 *lens_ipow(dx, 5) + 5.17997e-05 *lens_ipow(y, 3)*dx*dy + 7.4906e-05 *x*lens_ipow(y, 2)*lens_ipow(dx, 2) + 2.74846e-05 *lens_ipow(x, 3)*lens_ipow(dy, 2) + -0.349306 *lens_ipow(dx, 3)*lens_ipow(lambda, 4) + -4.04269e-06 *lens_ipow(y, 4)*lens_ipow(dx, 3) + 8.64061e-06 *x*lens_ipow(y, 3)*lens_ipow(dx, 2)*dy + -1.97928e-05 *lens_ipow(x, 2)*lens_ipow(y, 2)*dx*lens_ipow(dy, 2) + 3.02588e-06 *lens_ipow(x, 3)*y*lens_ipow(dy, 3) + -1.90092e-05 *lens_ipow(x, 4)*lens_ipow(dx, 3) + -0.383919 *dx*lens_ipow(dy, 2)*lens_ipow(lambda, 5)+0.0f;
const float dx43 =  + -0.0382226 *dy + -0.000255053 *y + 0.0116717 *y*lens_ipow(dy, 2) + 0.00373562 *y*lens_ipow(dx, 2) + 0.00714508 *x*dx*dy + -6.29131e-05 *x*y*dx + -3.25405 *lens_ipow(dy, 5) + -6.73223 *lens_ipow(dx, 2)*lens_ipow(dy, 3) + -3.424 *lens_ipow(dx, 4)*dy + 2.58999e-05 *lens_ipow(y, 3)*lens_ipow(dx, 2) + 7.66215e-05 *lens_ipow(x, 2)*y*lens_ipow(dy, 2) + 5.49691e-05 *lens_ipow(x, 3)*dx*dy + -0.282348 *lens_ipow(dy, 3)*lens_ipow(lambda, 3) + -1.92831e-05 *lens_ipow(y, 4)*lens_ipow(dy, 3) + 2.8802e-06 *x*lens_ipow(y, 3)*lens_ipow(dx, 3) + -1.97928e-05 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(dx, 2)*dy + 9.07765e-06 *lens_ipow(x, 3)*y*dx*lens_ipow(dy, 2) + -3.88118e-06 *lens_ipow(x, 4)*lens_ipow(dy, 3) + -0.383919 *lens_ipow(dx, 2)*dy*lens_ipow(lambda, 5)+0.0f;
const float dx44 =  + 0.195828  + -0.490568 *lens_ipow(lambda, 2) + -0.211761 *lens_ipow(dy, 4)*lens_ipow(lambda, 2) + -0.349306 *lens_ipow(dx, 4)*lens_ipow(lambda, 3) + 7.83318e-07 *lens_ipow(x, 2)*lens_ipow(y, 2)*lens_ipow(lambda, 3) + -0.959797 *lens_ipow(dx, 2)*lens_ipow(dy, 2)*lens_ipow(lambda, 4) + 3.29934 *lens_ipow(lambda, 10)+0.0f;