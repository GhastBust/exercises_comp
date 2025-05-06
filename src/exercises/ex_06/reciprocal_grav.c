#include "test_forces.h"

double p_grav_pot( const Particle* a, const Particle* b ) {
    double r = sqrt(particle_distance2(a, b));
    return - a->mass * b->mass * 0.01 /r;
}

vec3 p_grav_frc( const Particle *a, const Particle* b) {

    double r2 = particle_distance2(a, b);
    vec3 r_versor = particle_direction_versor(a, b);

    return cv3mult(-.01*a->mass * b->mass / r2, &r_versor);
}

void test_reciprocal_grav2( void ) {

    #define PARTICLES 2
    double side_len = 1000;
    double dt       = 0.0001;
    double T        = 40;

    Particle ps[PARTICLES] = {
        {0, 1, {{ 1,0,0}}, {{0,  .05,0}}},
        {1, 1, {{-1,0,0}}, {{0, -.05,0}}},
    };

    Particle np[PARTICLES] = {0};
    VernelSimulation sym = {
        .n_particles = PARTICLES, 
        .side_len = side_len, 
        .particles = ps, 
        .cache = np,
        .pforce = p_grav_frc,
        .ppot = p_grav_pot,
    };

    for ( double t = 0; t < T; t+= dt ) {
        if ( fmod(t, T/30) < dt) { print_sym(&sym, t); }
        step_all_vernel( &sym, dt);
    }

    print_sym(&sym, T);
}


