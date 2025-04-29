#include "test_forces.h"

double p_grav_pot( Particle* a, Particle* b ) {
    double r = sqrt(Pdistance2(a, b));
    return - a->mass * b->mass * 0.01 /r;
}

vec3 p_grav_frc( const Particle *p, const void *_sym ) {

    const VernelSimulation* sym = _sym;

    vec3 force = {0};
    vec3 f;
    Particle* q;
    double r2;

    for (int i = 0; i< sym->n_particles; i++) {
        q = sym->old_particles + i;
        if (p->id == q->id) {continue;}

        f = vvdiff(&q->pos, &p->pos);
        r2 = v3norm2(f) ;
        f = cv3mult(p->mass * q->mass * 0.01 / r2 / sqrt(r2), &f);

        force = vvadd(&force, &f);
    }

    return force;
}


void test_reciprocal_grav2p( void ) {
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

        if ( fmod(t, T/30) < dt) { print_sym(&sym, t, p_grav_pot, zero_p_pot); }

        step_all_vernel( &sym, c_grav_frc, dt);
    }

    print_sym(&sym, T, c_grav_pot, zero_p_pot);
};
