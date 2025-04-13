#include "vel-ver.h"

#include <malloc.h>
#include <math.h>
#include "../rand/rand.h"

typedef struct VernelSimulation {
    int     n_particles;
    Particle*   old_particles;
    Particle*   new_particles;
} VernelSimulation;


inline double Pdistance2( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return v3norm2(temp);
};

inline vec3 direct( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return cv3mult(1/sqrt(v3norm2(temp)), &temp);
};

double int_pow( double base, int exp ) {

    if (exp < 0) {
        base = 1/base;
        exp = -exp;
    }

    if (exp == 0) {return 1;}

    if ( exp == 2 ) { return base * base;}

    if (exp % 2 == 0) {
        double half_pow = int_pow(base, exp/2);
        return half_pow * half_pow;
    } else {
        double one_minus_pow = int_pow(base, exp-1);
        return one_minus_pow * base;
    }
}


inline vec3 get_force_between( const Particle* a, const Particle* b ) {

    double r = sqrt( Pdistance2(a, b) );

    double r6 = int_pow(r, 6);
    double r13 = r6 * r6 * r;

    double force = 6 * (r6 - 2) / r13;

    vec3 force3 = direct(a, b);
    
    force3 = cv3mult(force, &force3);

    return force3;
};

void swap_old_new( VernelSimulation* sym ) {
    Particle* temp = sym->old_particles;
    sym->old_particles = sym->new_particles;
    sym->new_particles = temp;
}

VernelSimulation init_simulation( size_t num_particles, double mass, double radius, int seed, double sigma ) {

    Particle* parray = calloc( num_particles * 2, sizeof(Particle) );

    RandGenerator R = init_random_generator(seed, sigma);

    for (size_t i = 0; i < num_particles; i++) {

        parray[i].id = i;
        parray[i].mass = mass;
        parray[i].pos = (vec3){{
            linear_rand(0, 100), 
            linear_rand(0, 100), 
            linear_rand(0, 100)
        }};
        parray[i].vel = (vec3){{
            gaussian_rand(&R),
            gaussian_rand(&R),
            gaussian_rand(&R)
        }};
    }

    return (VernelSimulation){ num_particles, parray, parray+num_particles};
};


vec3 LJ_force( const Particle* part, const void* vp_system ) {
        
    const VernelSimulation* system = (VernelSimulation*) vp_system; //! molto unsafe, ma unico modo di procedere

    vec3 current_force;
    vec3 force_on_particle = {0};

    for (int i = 0; i < system->n_particles; i++) {
        
        if ( i==part->id) {continue;}

        current_force = get_force_between(part, system->old_particles + i);

        force_on_particle = vvadd(&force_on_particle, &current_force);
    }

    return force_on_particle;
}
