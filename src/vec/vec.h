#ifndef __VEC_H__
#define __VEC_H__

#include <stdio.h>
#include <malloc.h>

struct Vec
{
    double* array;
    int len;
};

void printvec( struct Vec v);
struct Vec linspacee(double a, double b, int n);
struct Vec logspacee(double a, double b, int n);

#endif //__VEC_H__