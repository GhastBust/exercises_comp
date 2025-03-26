#ifndef __STAR_EX_H__
#define __STAR_EX_H__

#include <math.h>
#include "../matr/matr.h"
#include "runge_kutta.h"

//* Siano i tre parametri: 
//* 0) raggio
//* 1) massa
//* 2) pressione

static const double gamma_ = 5./3;
static const double K = 0.05;
// static const double gamma_ = 4./3;
// static const double K = 0.1;
// static const double gamma_ = 2.54;
// static const double K = 0.01;

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

void calculate_star_param() {

    double h = 1E-5;

    vec3 initial = {{1E-5, 0, 10}};

    txyvec results = { vcreate(), vcreate(), vcreate() };
    vec3 i_txy = initial;

    vappend( &results.t, i_txy.o[0] );
    vappend( &results.x, i_txy.o[1] );
    vappend( &results.y, i_txy.o[2] );

    while (i_txy.o[2] > 0 ) {
        i_txy = next_rk_step(i_txy, dmdr, dpdr, h);

        vappend( &results.t, i_txy.o[0] );
        vappend( &results.x, i_txy.o[1] );
        vappend( &results.y, i_txy.o[2] );
    }

    vvvprint(results);

}

#endif //__STAR_EX_H__