#include "trap.h"

#include "../../vec/vec.h"

double int_trap(double a, double b, double (*f)(double), int n)
{
    Vec v = linspacee(a, b, n);

    double sum = 0;
    double h = v.ptr[1] - a;

    for (unsigned i = 1; i < v.cap-1; i++)
    {
        sum += (*f)(*(v.ptr+i));
    }

    double I = h/2 * ((*f)(a) + (*f)(b)) + h*sum;

    vdestroy(&v);

    return I;
};