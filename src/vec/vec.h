#ifndef __VEC_H__
#define __VEC_H__

#include "../matr/matr.h"

typedef struct vec
{
    double* ptr;
    unsigned len;
    unsigned cap;
} vec;

typedef struct txyvec {
    vec t;
    vec x;
    vec y;
} txyvec;


vec     vcreate(void);
vec     vwith_cap( unsigned cap );
void    vappend( vec* v, double x );
void    vdestroy( vec* v);

void    printvec( vec v, char* format, char* sep );

void    vvvappend( txyvec* vvv, vec3 v );
void    vvvprint( txyvec v, char* format, char* sep );

vec linspacee(double a, double b, int n);
vec logspacee(double a, double b, int n);

#endif //__VEC_H__