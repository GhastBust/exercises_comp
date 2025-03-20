#ifndef __INTEGRAL_H__
#define __INTEGRAL_H__

#include <malloc.h>
#include "../../vec/vec.h"


double int_trap(double a, double b, double (*f)(double), int n)
{
    Vec v = linspacee(a, b, n);

    double sum = 0;
    double h = *(v.ptr+1) - *v.ptr;

    for (unsigned i = 1; i < v.len-1; i++)
    {
        sum += (*f)(*(v.ptr+i));
    }

    double I = h/2 * ((*f)(a) + (*f)(b)) + h*sum;

    free(v.ptr);

    return I;
};

#endif