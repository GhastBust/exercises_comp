#ifndef __VEL_VER_H__
#define __VEL_VER_H__

#include "../matr/matr.h"


typedef struct Particle {
    int  id;
    vec3    pos;
    vec3    vel;
} Particle;

vec2 step_vel_ver( vec2 x, double (*U) (double), double m, double dx, double dt );
Particle step_vernel_vec3( const Particle* x, double (*U) (const vec3*), double m, const vec3* dx, double dt );
Particle step_vernel_vec3_cforce( const Particle* x, vec3 (*f)(const void*), double m, double dt );


#endif//__VEL_VER_H__
