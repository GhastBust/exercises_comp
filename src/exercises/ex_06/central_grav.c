#include "test_forces.h"

vec3 c_grav_frc( const Particle *p, __attribute__((unused)) const void *__s ) { 
    double r3 = int_pow( sqrt(v3norm2(p->pos)), 3);
    r3 = fmax(r3, 1e-6);
    vec3 force = cv3mult( -p->mass * 1/r3 /100, &p->pos);

    return force;
}

double c_grav_pot( Particle* p ) {
    return - p->mass /100 / sqrt( v3norm2(p->pos) );
}

void test_central_grav( void ) {

    #define PARTICLES 1
    double side_len = 1000;
    double dt       = 0.00001;
    double T        = 40;

    Particle ps[PARTICLES] = {
        {0, 1, {{ 1,0,0}}, {{0, .1,0}}},
    };

    Particle n[PARTICLES] = {};
    VernelSimulation sym = {PARTICLES, side_len, ps, n};

    for ( double t = 0; t < T; t+= dt ) {

        if ( fmod(t, T/30) < dt) { print_sym(&sym, t, c_grav_pot, zero_p_pot); }

        step_all_vernel( &sym, c_grav_frc, dt);
    }

    print_sym(&sym, T, c_grav_pot, zero_p_pot);
}