#include "vel-ver.h"

#include <malloc.h>
#include <math.h>

#include "../diag/diag.h"
#include "../rand/rand.h"
#include "../mymath/mymath.h"


void __swap_old_new( VernelSimulation* sym ) {
    Particle* temp = sym->particles;
    sym->particles = sym->cache;
    sym->cache = temp;
}

void __mirror_particles( VernelSimulation* sym ) {

    for ( int i = 0; i < sym->n_particles; i++) {
        for (int j = 0; j < 3; j++) {
            sym->particles[i].pos.o[j] = fmod(sym->particles[i].pos.o[j] + sym->side_len, sym->side_len * 2 ) - sym->side_len;
        }
    }

}


// VernelSimulation init_simulation( size_t num_particles, double mass, double side_len, double init_square_side, int seed, double sigma ) {
VernelSimulation init_simulation( 
    size_t  num_particles, 
    double  side_len,
    double  mass, 
    int     seed, 
    double  sigma,
    vec3    (*cforce)(const Particle*),
    vec3    (*pforce)(const Particle*, const Particle*),
    double  (*cpot)(const Particle*),
    double  (*ppot)(const Particle*, const Particle*)
) {

    RandGenerator R = init_random_generator(seed, sigma);
    Particle* parray = calloc( num_particles * 2, sizeof(Particle) );

    //* particles per side
    size_t pps = ceil( cbrt(num_particles) ); 
    size_t pps2= pps*pps;

    double step = side_len/pps;
    vec3 p0 = (vec3){{step/2, step/2, step/2}};
    vec3 p1;

    for (size_t i = 0; i < num_particles; i++) {

        p1 = (vec3){{
            step * (i%pps),
            step * ((i%pps2)/pps),
            step * (i/pps2)
        }};

        parray[i].id = i;
        parray[i].mass = mass;
        parray[i].pos = vvadd(&p0, &p1);
        parray[i].vel = (vec3){{
            gaussian_rand(&R),
            gaussian_rand(&R),
            gaussian_rand(&R)
        }};
    }

    return (VernelSimulation){ 
        .n_particles    = num_particles, 
        .side_len       = side_len, 
        .particles  = parray,
        .cache  = parray+num_particles,    
        .cforce = cforce,   .pforce = pforce,
        .cpot   = cpot,     .ppot = ppot
    };
};


vec3 __get_central_force_on( const Particle* particle, const VernelSimulation* sym ) {
    if (sym->cforce == NULL) {return (vec3){{0}};}
    return (*sym->cforce)(particle);
};

vec3 __get_particle_force_on(const Particle* particle, const VernelSimulation* sym ) {
    
    vec3 total_force = (vec3){{0}};
    vec3 i_force;
    
    if ( sym->pforce == NULL ) { return total_force; }

    for( size_t i = 0; i < sym->n_particles; i++) {
        if ( particle->id == sym->particles[i].id ) {continue;} 

        i_force = (*sym->pforce)(particle, sym->particles + i);

        vvaddeq(&total_force, &i_force);
    }

    return total_force;
}

vec3 get_force_on(const Particle *particle, const VernelSimulation *sym)
{
    vec3 cforce = __get_central_force_on(particle, sym);
    vec3 pforce = __get_particle_force_on(particle, sym);
    return vvadd(&cforce, &pforce);
}

double __get_central_pot_on( const Particle* particle, const VernelSimulation* sym ) {
    if (sym->cpot == NULL) {return 0;}
    return (*sym->cpot)(particle);
};

double __get_particle_potential_on(const Particle* particle, const VernelSimulation* sym ) {
    
    if ( sym->ppot == NULL ) { return 0; }

    double total_pot = 0;
    
    for( size_t i = 0; i < sym->n_particles; i++) {
        if ( particle->id == sym->particles[i].id ) {continue;} 

        total_pot += (*sym->ppot)(particle, sym->particles + i);
    }

    return total_pot;
}

double get_potential_on(const Particle *particle, const VernelSimulation *sym)
{
    return __get_central_pot_on(particle, sym) + __get_particle_potential_on(particle, sym);
};


void step_all_vernel(VernelSimulation *sym, double dt) {

    for ( size_t i = 0; i < sym->n_particles; i++ ) {
        Particle new_p = step_vernel_vec3(sym->particles + i, sym, dt);
        sym->cache[i] = new_p;
    }

    __swap_old_new(sym);
    __mirror_particles(sym);
}

void print_sym( const VernelSimulation* sym, double time ) {
    printf("%7.2f, ", time);
    for (int i = 0; i < sym->n_particles; i++) {
        // particle_print(sym->old_particles+i, "{pos}, {vel}, ");
        particle_print(sym->particles+i, "{pos}, ");
    }
    printf("% .3e\n", get_energy(sym));
}


double get_kin_nrg( const Particle* p ) {
    return p->mass * v3norm2(&p->vel) / 2;
}


double get_energy( const VernelSimulation* sym ) {

    double K = 0;
    double U = 0;

    for (int i = 0; i < sym->n_particles; i++) {

        K += get_kin_nrg( sym->particles + i );
        U += __get_central_pot_on( sym->particles + i, sym);

        if ( sym->ppot == NULL ) {continue;}
        for (int j = i+1; j < sym->n_particles; j++ ) {
            U += (*sym->ppot)( sym->particles + i, sym->particles + j);
        }
    }

    return K + U;
}