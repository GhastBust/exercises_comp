#include "wave_func.h"

#include <math.h>

#include "../approx/fconst.h"
#include "../intt/simpson/simpson.h"

// double k = sqrt(2*uc2*(V0 - E)/hc/hc);
// double q = sqrt(2*uc2*E/hc/hc);
// double A = 1;
// double B = A * sin(k*R) / exp(-q*R);
// double remainder1 = B*B/4/q/q/q;
// double remainder2 = B*B/2/q;

const double k = 9.896845828952E-01;
const double q = 2.260923880842E-01;
const double A = 1.000000000000E+00;
const double B = 1.458864289061E+00;
const double remainder1 = 4.603752550284E+01;
const double remainder2 = 4.706671091256E+00;

double wave1(double r) { return A * sin(k*r); }
double wave2(double r) { return B * exp(-q*r); }

// double wave_func_u(double r) {
//     if (r > R) { return wave1(r); }
//     if (r <=R) { return wave2(r); }
//     return 0;
// };


double r2_u2(double r) {
    double r2 = r*r;

    double w1 = wave1(r);
    double w2 = wave2(r);

    w1 *= w1;
    w2 *= w2;

    return r2 * (w1-w2);
}

double u2(double r) {
    double w1 = wave1(r);
    double w2 = wave2(r);

    w1 *= w1;
    w2 *= w2;

    return w1 - w2;
}

double mean_r2() {

    double numerator = remainder1 + int_simp(0, R, r2_u2, 2000);

    double denominator = remainder2 + int_simp(0, R, u2, 2000);

    return numerator / denominator;

}