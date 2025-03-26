#include "vec.h"

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>

vec vcreate(void) {
    
    unsigned cap = 50;
    double* ptr = malloc( cap * sizeof(double) );
    unsigned len = 0;

    vec v = {ptr, len, cap};

    return v;
};

vec vwith_cap( unsigned cap ) {
    double* ptr = malloc( cap * sizeof(double) );
    unsigned len = 0;

    vec v = {ptr, len, cap};

    return v;
};

void vappend( vec* v, double x) {

    if ( v->len == v->cap ) { 

        vec v1 = vwith_cap(v->cap * 2);
        v1.len = v->len;

        memcpy(v1.ptr, v->ptr, v->cap * sizeof(double) );
        vdestroy(v);

        *v = v1;
    }

    v->ptr[v->len] = x;
    v->len++;

    return;
};

void vdestroy( vec* v ) {
    free(v->ptr);
    v->ptr = NULL;
    v->len = 0;
    v->cap = 0;
};


void printvec( vec v ) 
{
    for ( unsigned i = 0; i < v.len; i++)
    {
        printf("%e ", *(v.ptr + i));
    }
};

vec linspacee(double a, double b, int n) {
    double j;
    vec v = vwith_cap(n+1);
    
    for (unsigned i = 0; i < v.cap; i++)
    {
        j = (double)i / v.cap;

        vappend(&v, a + (b-a)*j);
    } 

    return v;
}

vec logspacee(double a, double b, int n) {
    double j;
    vec v = vwith_cap(n+1);
    
    for (unsigned i = 0; i < v.cap; i++)
    {
        j = (double)i / v.cap;

        vappend(&v, a * pow(b/a,j) );
    } 

    return v;
}