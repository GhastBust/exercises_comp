#ifndef __MYMATH_H__
#define __MYMATH_H__

#include "../matr/matr.h"

double int_pow( double base, int exp );
vec3 gradient_v3( double (*f) (const vec3*), const vec3* v, const vec3* dv );

#endif//__MYMATH_H__
