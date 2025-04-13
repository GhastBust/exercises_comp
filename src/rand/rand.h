#ifndef __RAND_H__
#define __RAND_H__

#include "../option/option.h"

typedef struct RandGenerator
{
    int     seed;
    double  sigma;
    Option  cached_result;
} RandGenerator;

RandGenerator init_random_generator( int seed, double sigma );
double linear_rand( double start, double end );
double gaussian_rand( RandGenerator* r_gen );

#endif//__RAND_H__
