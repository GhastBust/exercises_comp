#include "vel-ver.h"

#include <math.h>
#include <stdio.h>

#include "../approx/approx.h"


inline double Pdistance2( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return v3norm2(temp);
};

inline vec3 direct( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return cv3mult(1/sqrt(v3norm2(temp)), &temp);
};


inline double calc_new_pos( vec2 x, double (*U) (double), double m, double dx, double dt ) {

    #define F(y, dy) ( -der(U, (y), (dy)) )

    double xt = x.a;
    double vt = x.b;

    double dt2 = dt *dt;

    return xt + vt *dt - dt2 /(2*m) * F(xt, dx);
    
}

inline double calc_new_vel( vec2 x, double xtdt, double (*U) (double), double m, double dx ,double dt ) {

    #define F(y, dy) ( -der(U, (y), (dy)) )

    double xt = x.a;
    double vt = x.b;

    return vt + dt /2 /m *( F(xt, dx) + F(xtdt, dx) );
}

inline vec2 step_vel_ver( vec2 x, double (*U) (double), double m, double dx, double dt ) {

    double new_pos = calc_new_pos(x, U, m, dx, dt);

    double new_vel = calc_new_vel(x, new_pos, U, m, dx, dt);

    return (vec2){ new_pos, new_vel};

}


#define FORCE(x) (*(x))(const Particle*, const void *)

inline vec3 calc_new_pos_v3_cforce( const Particle* x, const void* sym, vec3 FORCE(f), double dt ) {
    
    double dt2 = dt *dt;

    vec3 xt         = x->pos;
    vec3 velterm    = cv3mult(dt, &x->vel);
    vec3 force      = (*f)(x, sym);
    vec3 accterm    = cv3mult( dt2 /(2*x->mass), &force);

    return mvvadd( 3, &xt, &velterm, &accterm ); 
}

inline vec3 calc_new_vel_v3_cforce( const Particle* x, const void* sym, const Particle* newx, vec3 FORCE(f), double dt ) {

    vec3 vt         = x->vel;
    vec3 f1         = (*f)(x, sym);
    vec3 f2         = (*f)(newx, sym);
    vec3 force      = vvadd( &f1, &f2 );
    vec3 accterm    = cv3mult( dt /2 /x->mass, &force);

    return vvadd( &vt, &accterm );
}


Particle step_vernel_vec3_cforce( 
    const Particle* x, 
    const void*     sym, 
    vec3            (*f) (const Particle*, const void *), 
    double          dt 
) {
    Particle new_part = {0};

    new_part.id = x->id;
    new_part.mass = x->mass;
    new_part.pos = calc_new_pos_v3_cforce(x, sym, f, dt);

    new_part.vel = calc_new_vel_v3_cforce(x, sym, &new_part, f, dt);

    return new_part;
};


void particle_print( Particle* p ) {

    printf("Particle:\n");
    printf("\tid: %2d\n", p->id);
    printf("\tpos: (%f, %f, %f)\n", p->pos.o[0], p->pos.o[1], p->pos.o[2]);
    printf("\tvel: (%f, %f, %f)\n", p->vel.o[0], p->vel.o[1], p->vel.o[2]);

}