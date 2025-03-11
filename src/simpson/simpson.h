#ifndef __SIMPSON_H__
#define __SIMPSON_H__

#include <malloc.h>
#include "../vec/vec.h"

double int_simp(double a, double b, double (*f)(double), int n)
{
    struct Vec v = linspacee(a, b, 2*n);

    double sum = 0;
    double h = *(v.array+1) - a;
    double xi;

    for (int i = 1; i < v.len-1; i++)
    {
        xi = *(v.array+i);

        switch (i%2)
        {
        case 0: //* i pari
            sum += 2 * (*f)(xi);
            break;
        
        case 1:  //* i dispari
            sum += 4 * (*f)(xi);
            break;
        };
    }

    double fa = (*f)(a);
    double fb = (*f)(b);

    double I = h/3 * ( fa + fb + sum );

    return I;
};

#endif //__SIMPSON_H__