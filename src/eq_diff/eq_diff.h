#ifndef __EQ_DIFF_H__
#define __EQ_DIFF_H__

#include "../vec/vec.h"

typedef struct {
    Vec t;
    Vec q;
    Vec p;
} tqp;


const double T = 1;
const double L = 1;
const double m = 1;
const double k = 1;


typedef struct
{
    double q;
    double p;
} vec2;

typedef struct mat2x2
{
    double a, b, c, d;
} mat2x2;




vec2 mvmult( mat2x2 M, vec2 v ) {
    double v1q = v.q * M.a + v.p * M.b;
    double v1p = v.q * M.c + v.p * M.d;

    vec2 v1 = {v1q, v1p};

    return v1;
};

mat2x2 cmmult( double c, mat2x2 M) {
    mat2x2 M1 = {M.a * c, M.b * c, M.c * c, M.d * c};

    return M1;
}


vec2 cvmult( double c, vec2 v )
{
    vec2 v1 = {v.q * c, v.p * c};

    return v1;
};


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

// tqp euler( double q0, double p0 ) {

// }


#endif//__EQ_DIFF_H__
