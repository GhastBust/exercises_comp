#include "rand.h"

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>


RandGenerator init_random_generator( int seed, double sigma ) {
    srand(seed);
    return (RandGenerator){ seed, sigma, None};
}

double linear_rand( double start, double end ) {
    double b = rand()/(RAND_MAX+1.);
    b *= end;
    b += start;

    return b;
}

double gaussian_rand( RandGenerator* r_gen ) {

    if ( r_gen->cached_result.is_some ) {
        double rand_n = r_gen->cached_result.value;
        r_gen->cached_result = None;
        
        return rand_n;
    }

    double a = rand()/(RAND_MAX+1.);
    double b = rand()/(RAND_MAX+1.);

    double rand1 = r_gen->sigma * sqrt(-2 *log(1-a)) * sin(2* M_PI* b);
    double rand2 = r_gen->sigma * sqrt(-2 *log(1-a)) * cos(2* M_PI* b);

    r_gen->cached_result = Some(rand2);

    return rand1;
}