#include "eq_diff.h"

// static const double T = 1;
// static const double L = 1;
static const double m = 1;
static const double k = 1;



vec2 step_euler0( vec2 qp, double h ) {

    mat2x2 M = {1, h/m, h*k, 1};
    
    return mvmult(M, qp);
}

vec2 step_euler1( vec2 qp, double h ) {
    
    double C = 1 /(1 + h *h *k /m);

    mat2x2 M = {1, h/m, -h*k, 1};

    vec2 v1 = mvmult(M, qp);
    v1      = cvmult(C, v1);

    return v1;
}

vec2 step_trapezoids( vec2 qp, double h ) {

    double h2 = h*h;
    double den = 4*m+k*h2;

    mat2x2 M = {4*m - k*h2, 4*h, -4*m*k*h, 4*m - k*h2};

    vec2 v1 = mvmult(M, qp);
    v1 = cvmult(1/den, v1);

    return v1;
}