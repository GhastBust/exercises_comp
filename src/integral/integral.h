#ifndef __
#include <malloc.h>

struct Vec
{
    double* array;
    int size;
};


struct Vec linspace(double a, double b, int n)
{
    double* array = (double*) calloc( n+1, sizeof(double) );
    struct Vec v = {array, n+1};
    
    double j = 0;

    for (int i = 0; i < v.size; i++)
    {
        j = i / v.size;

        *(v.array + i) = a * (1-j) + b*j;
    } 

    return v;
}

double intt(double a, double b, double (*f)(double), int n)
{

    struct Vec v = linspace(a, b, n);

    double h = *(v.array+1) - *v.array;

    double sum = 0;

    for (int i = 1; i < v.size-1; i++)
    {
        sum += f(*(v.array+i));
    }

    double I = h/2 * (f(a) + f(b)) + h*(sum);


    return I;
}