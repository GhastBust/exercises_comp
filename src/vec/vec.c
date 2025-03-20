#include "vec.h"

#include <stdio.h>
#include <malloc.h>
#include <memory.h>

Vec vcreate(void) {
    
    unsigned cap = 50;
    double* ptr = malloc( cap * sizeof(double) );
    unsigned len = 0;

    Vec v = {ptr, len, cap};

    return v;
};

Vec vwith_cap( unsigned cap ) {
    double* ptr = malloc( cap * sizeof(double) );
    unsigned len = 0;

    Vec v = {ptr, len, cap};

    return v;
};

void vappend( Vec* v, double x) {

    if ( v->len == v->cap ) { 

        Vec v1 = vwith_cap(v->cap * 2);
        v1.len = v->len;

        memcpy(v1.ptr, v->ptr, v->cap * sizeof(double) );
        destroy(*v);

        *v = v1;
    }

    v->ptr[v->len] = x;
    v->len++;

    return;
};

void destroy( Vec v ) {
    free(v.ptr);
};


void printvec( Vec v ) 
{
    for ( unsigned i = 0; i < v.len; i++)
    {
        printf("%e ", *(v.ptr + i));
    }
};

Vec linspacee(double a, double b, int n)
{
    double j;
    Vec v = vwith_cap(n+1);
    
    for (unsigned i = 0; i < v.len; i++)
    {
        j = (double)i / v.len;

        *(v.ptr + i) = a * (1-j) + b*j;
    } 

    return v;
}