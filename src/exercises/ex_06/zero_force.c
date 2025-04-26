#include "test_forces.h"

#define UNUSED __attribute__((unused))

vec3    zero_frc( UNUSED const Particle* __p,   UNUSED const void* __s )    { return (vec3){{0,0,0}}; };
double  zero_p_pot( UNUSED Particle * __a,        UNUSED Particle * __b )   { return 0; };
double  zero_c_pot( UNUSED Particle* )                                      { return 0; };


void test_zero_force( void ) {

    #define PARTICLES 1
    double side_len = 1000;
    double dt       = 0.00001;
    double T        = 40;

    Particle ps[PARTICLES] = {
        {0, 1, {{0,0,0}}, {{1, 0,0}}}
    };

    Particle n[PARTICLES] = {0};
    VernelSimulation sym = {PARTICLES, side_len, ps, n};

    for ( double t = 0; t < T; t+= dt ) {

        if ( fmod(t, T/30) < dt) { print_sym(&sym, t, zero_c_pot, zero_p_pot); }

        step_all_vernel( &sym, zero_frc, dt);
    }

    print_sym(&sym, T, zero_c_pot, zero_p_pot);
}