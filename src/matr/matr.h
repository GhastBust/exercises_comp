#ifndef __MATR_H__
#define __MATR_H__


typedef struct vec2
{
    double a;
    double b;
} vec2;


typedef struct mat2x2
{
    double o[4];
} mat2x2;


typedef struct vec3 {
    double o[3];
} vec3;


vec3    vminus( vec3 v ); 
double  v3norm2( vec3 v );
vec3    vvadd ( const vec3* a, const vec3* b);
vec3    mvvadd( int count, ... );
vec3    vvdiff( const vec3* a, const vec3* b);
double  vvscal( vec3 a, vec3 b);
vec3    cv3mult( double c, const vec3* v);

mat2x2  mfrom( double arr[4] );
vec2    mvmult( mat2x2 M, vec2 v );
mat2x2  cmmult( double c, mat2x2 M);
vec2    cvmult( double c, vec2 v );
double  det( mat2x2 M );
mat2x2  inv( mat2x2 M );

#endif//__MATR_H__
