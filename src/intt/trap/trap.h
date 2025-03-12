#ifndef __INTEGRAL_H__
#define __INTEGRAL_H__

#include <malloc.h>
#include "../../vec/vec.h"


double int_trap(double a, double b, double (*f)(double), int n)
{
    struct Vec v = linspacee(a, b, n);

    double sum = 0;
    double h = *(v.array+1) - *v.array;

    for (int i = 1; i < v.len-1; i++)
    {
        sum += (*f)(*(v.array+i));
    }

    double I = h/2 * ((*f)(a) + (*f)(b)) + h*sum;

    free(v.array);

    return I;
};

#endif