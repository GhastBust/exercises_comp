#ifndef __VEC_H__
#define __VEC_H__

typedef struct Vec
{
    double* ptr;
    unsigned len;
    unsigned cap;
} Vec;

Vec vcreate(void);
Vec vwith_cap( unsigned cap );
void vappend( Vec* v, double x );
void destroy( Vec* v);

void printvec( Vec v);
Vec linspacee(double a, double b, int n);
Vec logspacee(double a, double b, int n);

#endif //__VEC_H__