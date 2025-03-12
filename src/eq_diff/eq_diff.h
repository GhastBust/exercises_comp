#ifndef __EQ_DIFF_H__
#define __EQ_DIFF_H__

#include "../header.h"

typedef struct {
    struct Vec t;
    struct Vec q;
    struct Vec p;
} tqp;


const T = 1;
const L = 1;
const m = 1;
const k = 1;


typedef struct
{
    double q;
    double p;
} vec2;


vec2 euler0( double q0, double p0, double h ) {
    double q1 = q0      + p0 * h/m;
    double p1 = h*k* q0 + p0;

    vec2 f = {q1, p1};

    return f;
}

vec2 euler1( double q0, double p0, double h ) {
    
    double C = 1 / ( 1 + h * h * k / m );

    double q1 = q0      + h/m * p0;
    double p1 = -h*k*q0 + p0;

    q1 *= C;
    p1 *= C;

    vec2 f = {q1, p1};

    return f;
}

tqp euler( double q0, double p0 ) {

}


#endif//__EQ_DIFF_H__
