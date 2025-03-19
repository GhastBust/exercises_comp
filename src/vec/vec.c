#include "vec.h"

void printvec( struct Vec v) 
{
    for ( int i = 0; i < v.len; i++)
    {
        printf("%e ", *(v.array + i));
    }
};

struct Vec linspacee(double a, double b, int n)
{
    double j;
    double* array = (double*) calloc( n+1, sizeof(double) );
    struct Vec v = {array, n+1};
    
    for (int i = 0; i < v.len; i++)
    {
        j = (double)i / v.len;

        *(v.array + i) = a * (1-j) + b*j;
    } 

    return v;
}