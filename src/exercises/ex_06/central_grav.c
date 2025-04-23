#include "test_forces.h"



vec3 c_grav( const Particle *p, __attribute__((unused)) const void *__s ) { 
    double r3 = int_pow( sqrt(v3norm2(p->pos)), 3);
    r3 = fmax(r3, 1e-6);
    vec3 force = cv3mult( -p->mass * 1/r3 /100, &p->pos);

    return force;
}

vec3 p_grav( const Particle *p, const void *_sym ) {

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


double get_pot_nrg_grav( Particle* a, Particle* b ) {

    double r = sqrt(Pdistance2(a, b));
    return - a->mass * b->mass * 0.01 /r;
}


void force_test( void ) {

    double side_len = 1000;
    double dt       = 0.00001;
    double T        = 40;

    Particle ps[2] = {
        {0, 1, {{ 1,0,0}}, {{0, .1,0}}},
        {1, 1, {{0,0,0}}, {{0,0,0}}}
    };

    Particle n[2] = {0};
    VernelSimulation sym = {2, side_len, ps, n};

    for ( double t = 0; t < T; t+= dt ) {

        if ( fmod(t, T/30) < dt) { print_sym(&sym, t, get_pot_nrg_grav); }

        step_all_vernel( &sym, c_grav, dt);
    }

    print_sym(&sym, T, get_pot_nrg_grav);
}

