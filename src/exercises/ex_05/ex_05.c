#include "ex_05.h"

#include <math.h>
#include <stdio.h>

#include "../../matr/matr.h"
#include "../../runge_kutta/runge_kutta.h"

//* Siano i tre parametri: 
//* 0) raggio
//* 1) massa
//* 2) pressione

// static const double gamma_ = 5./3;
// static const double K = 0.05;
static const double gamma_ = 4./3;
static const double K = 0.1;
// static const double gamma_ = 2.54;
// static const double K = 0.01;

static double dens( double P ) {
    return pow( P /K /(gamma_ - 1), 1/gamma_);
}

double nrg_dens( double P ) {
    return dens(P) + P / (gamma_- 1 );
}

double r_dpdr( vec3 v ) {

    double r = v.o[0];
    double m = v.o[1];
    double P = v.o[2];

    double num = (P + nrg_dens(P)) * (m + r*r*r*P);
    double den = r* (r-2*m);

    return - num / den;
}

double r_dmdr( vec3 v ) {
    
    double r = v.o[0];
    double P = v.o[2];
    
    return r *r *nrg_dens(P);
}

vec3 r_calculate_radius_mass( double P ) {

    double h = 1e-6;

    vec3 initial = {{1e-5, 0, P}};

    vec3 i_txy = initial;
    vec3 last_txy = initial;

    while (i_txy.o[2] > 0 ) {
        last_txy = i_txy;
        i_txy = next_rk_step(i_txy, r_dmdr, r_dpdr, h);
    }

    last_txy.o[2] = P;

    return last_txy;
}


void r_calculate_star_param() {

    const double R0 = 20.061454744401846;
    const double M0 = 13.712505425250876;

    //* da 3 a 50km
    //* cioè da 0.3 a 5

    // double start = 3e-6;
    // double end  = 1.73205e+02;    
    double start = 2.15443e-02;
    double end  = 1e+8;    
    // double start = 3.73632e-07;
    // double end  = 1.53070e+05;

    int steps = 30;

    vec Ps = logspacee(start, end, steps);
    txyvec results = { vcreate(), vcreate(), vcreate() };

    vec3 i_rmp;

    for ( unsigned i = 0; i < Ps.len; i++ ) {

        if (i % 5 == 0) { printf( "%2ld%% done...\n", lround( (double)i /Ps.len *100) );}

        i_rmp = r_calculate_radius_mass(Ps.ptr[i]);

        i_rmp.o[0] *= R0;
        i_rmp.o[1] *= M0;

        vvvappend( &results, i_rmp );
    }

    vvvprint(results, "%6.2f, %6.2f, %.5e", NULL);
    // vvvprint(results, "%.10e, %.10e, %.10e", NULL);
}

