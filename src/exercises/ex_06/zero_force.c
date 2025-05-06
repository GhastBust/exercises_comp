#include "test_forces.h"

// #define UNUSED __attribute__((unused))

// vec3    zero_frc( UNUSED const Particle* __p,   UNUSED const void* __s )    { return (vec3){{0,0,0}}; };
// double  zero_p_pot( UNUSED Particle * __a,        UNUSED Particle * __b )   { return 0; };
// double  zero_c_pot( UNUSED Particle* )                                      { return 0; };


void test_zero_force( void ) {

    #define PARTICLES 1
    double side_len = 1000;
    double dt       = 0.00001;
    double T        = 40;

    Particle ps[PARTICLES] = {
        {0, 1, {{0,0,0}}, {{1, 0,0}}}
    };

    Particle np[PARTICLES] = {0};
    VernelSimulation sym = {
        .n_particles = PARTICLES, 
        .side_len = side_len, 
        .particles = ps, 
        .cache = np,
    };

    for ( double t = 0; t < T; t+= dt ) {

        if ( fmod(t, T/30) < dt) { print_sym(&sym, t); }

        step_all_vernel( &sym, dt);
    }

    print_sym(&sym, T);
}