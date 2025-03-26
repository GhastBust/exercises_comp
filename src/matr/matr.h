#ifndef __MATR_H__
#define __MATR_H__


typedef struct vec2
{
    double q;
    double p;
} vec2;


typedef struct mat2x2
{
    double a, b, c, d;
} mat2x2;


vec2    mvmult( mat2x2 M, vec2 v );
mat2x2  cmmult( double c, mat2x2 M);
vec2    cvmult( double c, vec2 v );
double  det( mat2x2 M );
mat2x2  inv( mat2x2 M );

#endif//__MATR_H__
