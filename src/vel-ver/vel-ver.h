#ifndef __VEL_VER_H__
#define __VEL_VER_H__

#include <stddef.h>

#include "../matr/matr.h"

typedef struct Particle {
    int     id;
    double  mass;
    vec3    pos;
    vec3    vel;
} Particle;


typedef struct VernelSimulation {
    int         n_particles;
    double      side_len;
    Particle*   old_particles;
    Particle*   new_particles;
    vec3      (*cforce )(const Particle*);
    vec3      (*pforce )(const Particle*, const Particle*);
    double    (*cpot   )(const Particle*);
    double    (*ppot   )(const Particle*, const Particle*);
} VernelSimulation;


vec2        step_vel_ver     ( vec2 x, double (*U) (double), double m, double dx, double dt );
Particle    step_vernel_vec3 ( const Particle *x, const VernelSimulation* sym, double dt );

double      particle_distance2        ( const Particle* a, const Particle* b );
vec3        particle_direction_versor ( const Particle* a, const Particle* b );

int         particle_print  ( const Particle* p,  const char* format );
int         particle_sprint ( char* buffer, const Particle* p, const char* format );


VernelSimulation init_simulation( 
    size_t  num_particles, 
    double  side_len,
    double  mass, 
    int     seed, 
    double  sigma,
    vec3    (*cforce)(const Particle*),
    vec3    (*pforce)(const Particle*, const Particle*),
    double  (*cpot)  (const Particle*),
    double  (*ppot)  (const Particle*, const Particle*)
);

void        step_all_vernel (   VernelSimulation* sym, double dt );

vec3        get_force_on     ( const Particle* particle, const VernelSimulation* sym);
double      get_potential_on ( const Particle* particle, const VernelSimulation* sym);
double      get_kin_nrg      ( const Particle* p );
double      get_energy       ( const VernelSimulation* sym );

void        print_sym        ( const VernelSimulation* sym, double time );

#endif//__VEL_VER_H__
