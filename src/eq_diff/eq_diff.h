#ifndef __EQ_DIFF_H__
#define __EQ_DIFF_H__

#include "../vec/vec.h"

typedef struct {
    Vec t;
    Vec q;
    Vec p;
} tqp;



typedef struct
{
    double q;
    double p;
} vec2;

typedef struct mat2x2
{
    double a, b, c, d;
} mat2x2;




vec2 mvmult( mat2x2 M, vec2 v );

mat2x2 cmmult( double c, mat2x2 M);


vec2 cvmult( double c, vec2 v );


vec2 step_euler0( vec2 qp, double h );

vec2 step_euler1( vec2 qp, double h );

vec2 step_trapezoids( vec2 qp, double h );

// tqp euler( double q0, double p0 ) {

// }


#endif//__EQ_DIFF_H__
