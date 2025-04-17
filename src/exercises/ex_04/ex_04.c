#include "ex_04.h"

#include <stdio.h>
#include <math.h>

#include "../../matr/matr.h"
#include "../../runge_kutta/runge_kutta.h"
#include "../../eq_diff/eq_diff.h"


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

static double dens( double P ) {
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

vec3 calculate_radius_mass( double P, double h) {

    vec3 initial = {{1e-5, 0, P}};

    vec3 i_txy = initial;
    vec3 last_txy = initial;

    while (i_txy.o[2] > 0 ) {
        last_txy = i_txy;
        i_txy = next_rk_step(i_txy, dmdr, dpdr, h);
    }

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

    int steps = 150;

    vec Ps = logspacee(start, end, steps);
    txyvec results = { vcreate(), vcreate(), vcreate() };

    vec3 i_rmp;

    for ( unsigned i = 0; i < Ps.len; i++ ) {

        if (i % 5 == 0) { printf( "%2ld%% done...\n", lround( (double)i /Ps.len *100) );}

        i_rmp = calculate_radius_mass(Ps.ptr[i], 1e-6);

        i_rmp.o[0] *= R0;
        i_rmp.o[1] *= M0;

        vvvappend( &results, i_rmp );
    }

    // vvvprint(results, "%6.2f, %6.2f, %.5e", NULL);
    vvvprint(results, "%.10e, %.10e, %.10e", NULL);
}

vec3 df_stella( const vec3* x, double h ) {
    vec3 df = (vec3){{h, dmdr(*x), dpdr(*x)}};

    return vvadd(x, &df);
}

vec3 calculate_radius_mass_euler( double P0, double h ) {

    vec3 initial = {{1e-5, 0, P0}};

    vec3 i_txy = initial;
    vec3 last_txy = initial;

    while (i_txy.o[2] > 0 ) {
        last_txy = i_txy;
        i_txy = step_eulero_stella(&i_txy, df_stella, h);
    }

    last_txy.o[2] = P0;

    return last_txy;
}


void multv_append( vec* v, int len, const double* to_append ) {
    
    for ( int j = 0; j < len; j++ ) {
        vappend( v+j, to_append[j] );
    }

    return;
}

void multv_print( const vec* v, int len ) {
    
    for ( unsigned i = 0; i < v->len; i++ ) {
        for ( int j = 0; j < len; j++ ) {
            printf("% .10e, ", v[j].ptr[i]);
        }
        printf("\n");
    }

    return;
}


void calculate_with_euler( void ) {

    const double R0 = 20.061454744401846;
    // const double M0 = 13.712505425250876;

    //* da 3 a 50km
    //* cioè da 0.3 a 5

    const double P0 = 1;

    const double start = 1;
    const double end  = 1e-8;

    const int steps = 30;
    vec results[] = { vwith_cap(steps+1), vwith_cap(steps+1), vwith_cap(steps+1), vwith_cap(steps+1), vwith_cap(steps+1) };
    double to_append[5] = {0};

    vec3 i_rmp;
    double r_err_eu_i;    
    double m_err_eu_i;
    double r_err_rk_i;
    double m_err_rk_i;

    const vec hs = logspacee(start, end, steps);

    const vec3 max_prec_res_rk = calculate_radius_mass(P0, fmin(start, end));
    const double r_max_prec = max_prec_res_rk.o[0];
    const double m_max_prec = max_prec_res_rk.o[1];

    for ( unsigned i = 0; i < hs.len; i++ ) {

        if (i % 5 == 0) { printf( "%2ld%% done...\n", lround( (double)i /hs.len *100) );}

        i_rmp = calculate_radius_mass_euler(P0, hs.ptr[i]);

        r_err_eu_i = (i_rmp.o[0] / r_max_prec) -1;
        m_err_eu_i = (i_rmp.o[1] / m_max_prec) -1;

        i_rmp = calculate_radius_mass(P0,  hs.ptr[i]);

        r_err_rk_i = (i_rmp.o[0] / r_max_prec) -1;
        m_err_rk_i = (i_rmp.o[1] / m_max_prec) -1;

        to_append[0] = r_err_eu_i;
        to_append[1] = m_err_eu_i;
        to_append[2] = r_err_rk_i;
        to_append[3] = m_err_rk_i;
        to_append[4] = hs.ptr[i] * R0;

        multv_append( results, 5, to_append );
    }
 
    multv_print( results, 5 );
}