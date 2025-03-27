#ifndef __STAR_EX_H__
#define __STAR_EX_H__

#include <math.h>
#include "../matr/matr.h"
#include "runge_kutta.h"

//* Siano i tre parametri: 
//* 0) raggio
//* 1) massa
//* 2) pressione

// static const double gamma_ = 5./3;
// static const double K = 0.05;
// static const double gamma_ = 4./3;
// static const double K = 0.1;
static const double gamma_ = 2.54;
static const double K = 0.01;

double dens( double P ) {
    return pow( P /K /(gamma_ - 1), 1/gamma_);
}

double dpdr( vec3 v ) {

    double r = v.o[0];
    double m = v.o[1];
    double P = v.o[2];

    return -(m * dens(P)) /r /r;
}

double dmdr( vec3 v ) {
    
    double r = v.o[0];
    // double m = v.o[1];
    double P = v.o[2];
    
    return r *r *dens(P);
}

void vvvappend( txyvec* vvv, vec3 v ) {
    vappend( &vvv->t, v.o[0] );
    vappend( &vvv->x, v.o[1] );
    vappend( &vvv->y, v.o[2] );
}

vec3 calculate_radius_mass( double P ) {

    double h = 1e-6;

    vec3 initial = {{1e-5, 0, P}};

    // txyvec results = { vcreate(), vcreate(), vcreate() };
    vec3 i_txy = initial;
    vec3 last_txy = initial;
    int j = 0;

    while (i_txy.o[2] > 0 ) {

        // printf("Iteration j = %d\n", j);
        j++;

        last_txy = i_txy;

        // vvvappend(&results, i_txy);

        i_txy = next_rk_step(i_txy, dmdr, dpdr, h);
    }

    // vvvprint(results);

    last_txy.o[2] = P;

    return last_txy;
}


void calculate_star_param() {

    const double R0 = 20.061454744401846;
    const double M0 = 13.712505425250876;

    //* da 3 a 50km
    //* cioè da 0.3 a 5

    // double start = 4.36516e-06;
    // double end  = 1.2e7;    
    // double start = 3.19736e-02;
    // double end  = 2.77223e+03;    
    double start = 3.73632e-07;
    double end  = 1.53070e+05;

    // int steps_per_mag = 10;

    // int steps = round( log10(end/start) ) *steps_per_mag;
    int steps = 150;

    vec Ps = logspacee(start, end, steps);
    txyvec results = { vcreate(), vcreate(), vcreate() };

    vec3 i_rmp;

    for ( unsigned i = 0; i < Ps.len; i++ ) {

        if (i % 5 == 0) { printf( "%2ld%% done...\n", lround( (double)i /Ps.len *100) );}

        i_rmp = calculate_radius_mass(Ps.ptr[i]);

        i_rmp.o[0] *= R0;
        i_rmp.o[1] *= M0;

        vvvappend( &results, i_rmp );
    }

    // vvvprint(results, "%6.2f, %6.2f, %.5e", NULL);
    vvvprint(results, "%.10e, %.10e, %.10e", NULL);
}


#endif //__STAR_EX_H__