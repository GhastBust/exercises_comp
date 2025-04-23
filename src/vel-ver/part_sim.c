#include "vel-ver.h"

#include <malloc.h>
#include <math.h>
#include "../rand/rand.h"
#include "../mymath/mymath.h"



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

    for ( int i = 0; i < sym->n_particles; i++) {
        for (int j = 0; j < 3; j++) {
            sym->old_particles[i].pos.o[j] = fmod(sym->old_particles[i].pos.o[j] + sym->size_len, sym->size_len * 2 ) - sym->size_len;
        }
    }

}

VernelSimulation init_simulation( size_t num_particles, double mass, double side_len, double init_square_side, int seed, double sigma ) {

    Particle* parray = calloc( num_particles * 2, sizeof(Particle) );

    RandGenerator R = init_random_generator(seed, sigma);

    for (size_t i = 0; i < num_particles; i++) {

        parray[i].id = i;
        parray[i].mass = mass;
        parray[i].pos = (vec3){{
            linear_rand(0, init_square_side ), 
            linear_rand(0, init_square_side ),
            linear_rand(0, init_square_side )
        }};
        parray[i].vel = (vec3){{
            gaussian_rand(&R),
            gaussian_rand(&R),
            gaussian_rand(&R)
        }};
    }

    return (VernelSimulation){ num_particles, side_len, parray, parray+num_particles};
};


Particle mirror_particle( const Particle* a, double side_len, const Particle* b ) {

    vec3 new_pos    = b->pos;
    vec3 diff       = vvdiff(&a->pos, &b->pos);

    for (int i = 0; i < 3; i++) {
        if ( diff.o[i] > side_len/2 ) {
            
            if ( a->pos.o[i] < side_len/2) {
                new_pos.o[i] -= side_len;
            } else {
                new_pos.o[i] += side_len;
            }
        }
    }

    return (Particle){b->id, b->mass, new_pos, b->vel};
}


vec3 LJ_force( const Particle* part, const void* vp_system ) {
        
    const VernelSimulation* sym = (VernelSimulation*) vp_system; //! molto unsafe, ma unico modo di procedere

    vec3 current_force;
    vec3 force_on_particle = {0};

    for (int i = 0; i < sym->n_particles; i++) {
        
        if ( i == part->id ) {continue;}

        Particle mirrored = mirror_particle(part, sym->size_len, sym->old_particles + i);

        current_force = get_force_between(part, &mirrored);

        force_on_particle = vvadd(&force_on_particle, &current_force);
    }

    return force_on_particle;
}


void step_all_vernel(VernelSimulation *sym, vec3 (*force)(const Particle *, const void *), double dt) {

    for ( int i = 0; i < sym->n_particles; i++ ) {
        Particle new_p = step_vernel_vec3_cforce(sym->old_particles + i, sym, force, dt);

        sym->new_particles[i] = new_p;
    }

    swap_old_new(sym);
}