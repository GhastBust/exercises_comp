#include "test_forces.h"

double get_pot_nrg_grav( Particle* a, Particle* b ) {

    double r = sqrt(Pdistance2(a, b));
    return - a->mass * b->mass * 0.01 /r;
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