#include "vel-ver.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../diag/diag.h"
#include "../approx/approx.h"


double Pdistance2( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return v3norm2(temp);
};

vec3 direct( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return cv3mult(1/sqrt(v3norm2(temp)), &temp);
};


double calc_new_pos( vec2 x, double (*U) (double), double m, double dx, double dt ) {

    #define F(y, dy) ( -der(U, (y), (dy)) )

    double xt = x.a;
    double vt = x.b;

    double dt2 = dt *dt;

    return xt + vt *dt - dt2 /(2*m) * F(xt, dx);
    
}

double calc_new_vel( vec2 x, double xtdt, double (*U) (double), double m, double dx ,double dt ) {

    #define F(y, dy) ( -der(U, (y), (dy)) )

    double xt = x.a;
    double vt = x.b;

    return vt + dt /2 /m *( F(xt, dx) + F(xtdt, dx) );
}

vec2 step_vel_ver( vec2 x, double (*U) (double), double m, double dx, double dt ) {

    double new_pos = calc_new_pos(x, U, m, dx, dt);

    double new_vel = calc_new_vel(x, new_pos, U, m, dx, dt);

    return (vec2){ new_pos, new_vel};

}


#define CFORCE(x) (*(x))(const Particle*)
#define PFORCE(x) (*(x))(const Particle*, const Particle*)

vec3 calc_new_pos_v3_cforce( const Particle* x, const void* sym, vec3 CFORCE(fc), vec3 PFORCE(fp), double dt ) {
    
    double dt2 = dt *dt;

    vec3 xt         = x->pos;
    vec3 cforce      = (*fc)(x, sym);
    vec3 velterm    = cv3mult(dt, &x->vel);
    vec3 accterm    = cv3mult( dt2 /(2*x->mass), &cforce);

    return mvvadd( 3, &xt, &velterm, &accterm ); 
}

vec3 calc_new_vel_v3_cforce( const Particle* x, const void* sym, const Particle* newx, vec3 CFORCE(f), double dt ) {

    vec3 vt         = x->vel;
    vec3 f1         = (*f)(x, sym);
    vec3 f2         = (*f)(newx, sym);
    vec3 force      = vvadd( &f1, &f2 );
    vec3 accterm    = cv3mult( dt /2 /x->mass, &force);

    return vvadd( &vt, &accterm );
}


Particle step_vernel_vec3( 
    const Particle* x, 
    const void*     sym, 
    vec3            (*fc) (const Particle*),
    vec3            (*fp) (const Particle*, const Particle*),
    double          dt 
) {
    Particle new_part = {0};

    new_part.id = x->id;
    new_part.mass = x->mass;
    new_part.pos = calc_new_pos_v3_cforce(x, sym, fc, dt);

    new_part.vel = calc_new_vel_v3_cforce(x, sym, &new_part, fc, dt);

    return new_part;
}


IOption find_str( const char* haystack, const char* needle ) {

    char* pos = strstr(haystack, needle);

    if (!pos) { return INone; } 

    return ISome(pos - haystack);
}


int particle_sprint( char* buffer, Particle* p, const char* format ) {

    IOption id_index  = find_str(format, "{id}");
    IOption pos_index = find_str(format, "{pos}");
    IOption vel_index = find_str(format, "{vel}");

    int i = 0;
    int j = 0;

    while (format[i]) {

        if ( id_index.value == i && id_index.is_some ) {
            j += sprintf( buffer+j, "%d", p->id );
            i += 4;
            continue;
        }
        
        if ( pos_index.value == i && pos_index.is_some ) {
            j += sprintf( buffer+j, "%f, %f, %f", p->pos.o[0], p->pos.o[1], p->pos.o[2] );
            i += 5;
            continue;
        }

        if ( vel_index.value == i && vel_index.is_some ) {
            j += sprintf( buffer+j, "%f, %f, %f", p->vel.o[0], p->vel.o[1], p->vel.o[2] );
            i += 5;
            continue;
        }

        buffer[j] = format[i];
        i++;
        j++;
    }

    return j;
}


void particle_print( Particle* p, const char* format ) {

    char buffer[150] = {};

    IOption id_index  = find_str(format, "{id}");
    IOption pos_index = find_str(format, "{pos}");
    IOption vel_index = find_str(format, "{vel}");

    int i = 0;
    int j = 0;

    while (format[i]) {

        if ( id_index.value == i && id_index.is_some ) {
            j += sprintf( buffer+j, "%d", p->id );
            i += 4;
            continue;
        }
        
        if ( pos_index.value == i && pos_index.is_some ) {
            j += sprintf( buffer+j, "%6.3f, %6.3f, %6.3f", p->pos.o[0], p->pos.o[1], p->pos.o[2] );
            i += 5;
            continue;
        }

        if ( vel_index.value == i && vel_index.is_some ) {
            j += sprintf( buffer+j, "%6.3f, %6.3f, %6.3f", p->vel.o[0], p->vel.o[1], p->vel.o[2] );
            i += 5;
            continue;
        }

        buffer[j] = format[i];
        i++;
        j++;
    }

    printf("%s", buffer);
}

