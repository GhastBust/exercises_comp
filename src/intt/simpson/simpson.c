#include "simpson.h"

#include "../../vec/vec.h"

double int_simp(double a, double b, double (*f)(double), int n)
{
    Vec v = linspacee(a, b, 2*n);

    double sum = 0;
    double h = *(v.ptr+1) - a;
    double xi;

    for (unsigned i = 1; i < v.len-1; i++)
    {
        xi = *(v.ptr+i);

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

    destroy(&v);

    return I;
};