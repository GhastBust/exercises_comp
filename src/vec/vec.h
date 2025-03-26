#ifndef __VEC_H__
#define __VEC_H__

typedef struct vec
{
    double* ptr;
    unsigned len;
    unsigned cap;
} vec;

vec vcreate(void);
vec vwith_cap( unsigned cap );
void vappend( vec* v, double x );
void vdestroy( vec* v);

void printvec( vec v);
vec linspacee(double a, double b, int n);
vec logspacee(double a, double b, int n);

#endif //__VEC_H__