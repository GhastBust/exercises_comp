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


vec2 __attribute__ ((noinline)) euler0( double q0, double p0, double h ) {
    double q1 = q0      + p0 * h/m;
    double p1 = h*k* q0 + p0;

    vec2 f = {q1, p1};

    return f;
}

vec2 __attribute__ ((noinline)) euler1( double q0, double p0, double h ) {
    
    double C = 1 / ( 1 + h * h * k / m );

    double q1 = q0      + h/m * p0;
    double p1 = -h*k*q0 + p0;

    q1 *= C;
    p1 *= C;

    vec2 f = {q1, p1};

    return f;
}

vec2 __attribute__ ((noinline)) trapezoids( double q0, double p0, double h ) {

    double h2 = h*h;
    double den = 4*m+k*h2;

    double lambda = (4*m - k*h2) / den;
    double lambda1 = 4*h / den;
    double lambda2 = -4*m*k*h / den;

    double q1 = q0 * lambda  + p0 * lambda1;
    double p1 = q0 * lambda2 + p0 * lambda;

    vec2 f = {q1, p1};

    return f;
}

// tqp euler( double q0, double p0 ) {

// }


#endif//__EQ_DIFF_H__
