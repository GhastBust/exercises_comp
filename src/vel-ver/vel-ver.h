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

vec2        step_vel_ver    ( vec2 x, double (*U) (double), double m, double dx, double dt );
Particle    step_vernel_vec3( const Particle *x, const void* sym, vec3 (*f)(const Particle*, const void *), double dt );
double      Pdistance2      ( const Particle* a, const Particle* b );
vec3        direct          ( const Particle* a, const Particle* b );
int         particle_sprint ( char* buffer, Particle* p, const char* format );
void        particle_print  ( Particle* p,  const char* format );


typedef struct VernelSimulation {
    int     n_particles;
    double  size_len;
    Particle*   old_particles;
    Particle*   new_particles;
} VernelSimulation;


void        swap_old_new( VernelSimulation* sym );
VernelSimulation init_simulation( size_t num_particles, double mass, double side_len, double init_square_len, int seed, double sigma );
vec3        LJ_force( const Particle* part, const void* vp_system );
void        step_all_vernel ( VernelSimulation* sym, vec3 (*force)(const Particle*, const void *), double dt );
void        print_sym( VernelSimulation* sym, double time, double (*Uc)(Particle*), double (*Up)(Particle*, Particle*) );
double      get_kin_nrg( Particle* p );
double      calc_nrg( VernelSimulation* sym, double (*Uc)(Particle*), double (*Uf)(Particle*, Particle*) );


#endif//__VEL_VER_H__
