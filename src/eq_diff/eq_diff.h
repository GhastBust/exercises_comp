#ifndef __EQ_DIFF_H__
#define __EQ_DIFF_H__

#include "../vec/vec.h"
#include "../matr/matr.h"

// typedef struct {
//     vec t;
//     vec q;
//     vec p;
// } tqp;


// vec2 step_euler0( vec2 qp, double h );

// vec2 step_euler1( vec2 qp, double h );

// vec2 step_trapezoids( vec2 qp, double h );

vec3 step_eulero_stella( const vec3* x, vec3 (*f)(const vec3*, double ), double h);


// tqp euler( double q0, double p0 ) {

// }


#endif//__EQ_DIFF_H__
