#ifndef __INTEGRAL_H__
#define __INTEGRAL_H__

#include <malloc.h>

typedef struct 
{
    double* array;
    int size;
} Vec;

void printvec( Vec v) 
{
    for ( int i = 0; i < v.size; i++)
    {
        printf("%e ", *(v.array + i));
    }
}


Vec linspace(double a, double b, int n)
{
    double j;
    double* array = (double*) calloc( n+1, sizeof(double) );
    Vec v = {array, n+1};
    
    for (int i = 0; i < v.size; i++)
    {
        j = (double)i / v.size;

        *(v.array + i) = a * (1-j) + b*j;
    } 

    return v;
}

double intt(double a, double b, double (*f)(double), int n)
{
    Vec v = linspace(a, b, n);

    double sum = 0;
    double h = *(v.array+1) - *v.array;

    for (int i = 1; i < v.size-1; i++)
    {
        sum += (*f)(*(v.array+i));
    }

    double I = h/2 * ((*f)(a) + (*f)(b)) + h*sum;


    return I;
}

#endif