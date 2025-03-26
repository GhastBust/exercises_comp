#ifndef __RUNGE_KUTTA_H__
#define __RUNGE_KUTTA_H__

#include "../matr/matr.h"
#include "../vec/vec.h"

typedef struct txyvec {
    vec t;
    vec x;
    vec y;
} txyvec;


void    vvvprint(txyvec v);
txyvec  exe_runge_kutta( vec3 initial, double final, double(*f)(vec3), double(*g)(vec3), double h );
vec3    next_rk_step( vec3 v, double(*f)(vec3), double(*g)(vec3), double h );

#endif//__RUNGE_KUTTA_H__
