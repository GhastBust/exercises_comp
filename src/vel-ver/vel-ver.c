#include "vel-ver.h"

#include "../approx/approx.h"


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


vec3 gradient_v3( double (*f) (const vec3*), const vec3* v, const vec3* dv ) {

    vec3 res;

    double f1;
    double f2;

    vec3 dxyz[3] = {    
        (vec3) {{1, 0, 0}},
        (vec3) {{0, 1, 0}},
        (vec3) {{0, 0, 1}},
    };

    for (int i = 0; i < 3; i++) {
        dxyz[i].o[i] = dv->o[i];
    }

    for (int i = 0; i < 3; i++) {

        vec3 dif = vvdiff(v, &dxyz[i]);
        vec3 add = vvadd (v, &dxyz[i]);

        f1 = (*f)( &dif );
        f2 = (*f)( &add );
    
        res.o[i] = (f2-f1) /2 / dv->o[i];
    }

    return res;
}

inline vec3 calc_new_pos_v3( const Particle* x, double (*U) (const vec3*), double m, const vec3* dx, double dt ) {

    #define G(y, dy) ( vminus(gradient_v3(U, (y), (dy)))  )
    
    double dt2 = dt *dt;

    auto xt         = x->pos;
    vec3 velterm    = cv3mult(dt, &x->vel);
    vec3 force      = G(&xt, dx);
    vec3 accterm    = cv3mult( dt2 /(2*m), &force);

    return mvvadd( 3, &xt, &velterm, &accterm ); 
}

inline vec3 calc_new_vel_v3( const Particle* x, const vec3* newpos, double (*U) (const vec3*), double m, const vec3* dx, double dt ) {

    #define G(y, dy) ( vminus(gradient_v3(U, (y), (dy)))  )

    vec3 xt         = x->pos;
    vec3 vt         = x->vel;
    vec3 f1         = G(&xt, dx);
    vec3 f2         = G(newpos, dx);
    vec3 force      = vvadd( &f1, &f2 );
    vec3 accterm    = cv3mult( dt /2 /m, &force);

    return vvadd( &vt, &accterm );
}


// inline Particle step_vernel_vec3( const Particle* x, double (*U) (const vec3*), double m, const vec3* dx, double dt ) {

//     vec3 new_pos = calc_new_pos_v3(x, U, m, dx, dt);

//     vec3 new_vel = calc_new_vel_v3(x, &new_pos, U, m, dx, dt);

//     return (Particle){ x->id, new_pos, new_vel};
// }


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

    // vec3 xt         = x->pos;
    vec3 vt         = x->vel;
    vec3 f1         = (*f)(x, sym);
    vec3 f2         = (*f)(newx, sym);
    vec3 force      = vvadd( &f1, &f2 );
    vec3 accterm    = cv3mult( dt /2 /x->mass, &force);

    return vvadd( &vt, &accterm );
}


Particle step_vernel_vec3_cforce( const Particle *x, const void* sym, vec3 FORCE(f), double dt )
{
    Particle new_part = {0};

    new_part.id = x->id;
    new_part.mass = x->mass;
    new_part.pos = calc_new_pos_v3_cforce(x, sym, f, dt);

    new_part.vel = calc_new_vel_v3_cforce(x, sym, &new_part, f, dt);

    return new_part;
};
