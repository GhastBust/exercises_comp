#include "ex_06.h"

#include <math.h>
#include <malloc.h>

#include "../../vel-ver/vel-ver.h"
#include "../../output/output.h"
#include "../../matr/matr.h"
#include "../../mymath/mymath.h"

// static const double epsilon = 1;
// static const double sigma = 1;
// static const double kB = 1;


double harmonic_pot( double q ) {
    
    double K = 1;

    return K /2 *q *q;

}

double harmonic_herm( vec2 x ) {
    return 1. /2 *x.b *x.b + 1. /2 *x.a *x.a;
}


void calc_harmonic( void ) {

    vec2 x = {1, 0};

    double T = 20;
    double dt = 1e-4;

    csv_open_write("data/harmonic_vel-ver.csv");

    for (double t = 0; t < T; t += dt) {

        x = step_vel_ver(x, harmonic_pot, 1, 1e-4, dt);

        csv_write(x.a);
        csv_write(x.b);
        csv_write(harmonic_herm(x));
        csv_new_line();

    }

    csv_close();
}


double calc_temp( const VernelSimulation* sym ) {

    double temperatue = 0;

    for (int i = 0; i < sym->n_particles; i++) {
        temperatue = v3norm2(sym->old_particles[i].vel) * sym->old_particles[i].mass;
    }

    temperatue /= 3 *sym->n_particles;

    return temperatue;
}


void calc_LJ_fluid_sim( void ) {

    int particles   = 2;
    double mass     = 1;
    double side_len = 100;
    double init_sq  = 10;
    int seed        = 874512;
    double sigma    = 5;
    double dt       = 0.001;
    double T        = 2000;

    VernelSimulation sym = init_simulation( particles, mass, side_len, init_sq, seed, sigma);

    for ( double t = 0; t < T; t+= dt ) {

        // if ( fmod(t, T/10) < dt) {
        //     printf("%f\n", calc_temp(&sym));
    
        //     for (int i = 0; i < sym.n_particles; i++) {
        //         particle_print(&sym.old_particles[i]);
        //     }
        // }

        for ( int i = 0; i < particles; i++) {
            Particle* p = sym.old_particles + i;
            Particle new_p = step_vernel_vec3_cforce(p, &sym, LJ_force, dt);
    
            sym.new_particles[i] = new_p;
        }

        swap_old_new(&sym);
    }
}


vec3 zero( __attribute__((unused)) const Particle* __p, __attribute__((unused)) const void* __s ) {return (vec3){{0,0,0}}; };

vec3 c_grav( const Particle *p, __attribute__((unused)) const void *__s ) { 
    double r3 = int_pow( sqrt(v3norm2(p->pos)), 3);
    r3 = fmax(r3, 1e-6);
    vec3 force = cv3mult( -p->mass * 1/r3 /100, &p->pos);

    return force;
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


double get_kin_nrg( Particle* p ) {
    return p->mass * v3norm2(p->vel) / 2;
}

double get_pot_nrg_grav( Particle* a, Particle* b ) {

    double r = sqrt(Pdistance2(a, b));
    return - a->mass * b->mass * 0.01 /r;
}


double calc_nrg( VernelSimulation* sym, double (*Uf)(Particle*, Particle*) ) {

    double K = 0;
    double U = 0;

    for (int i = 0; i < sym->n_particles; i++) {

        K += get_kin_nrg( sym->old_particles + i );

        for (int j = i+1; j < sym->n_particles; j++ ) {
            U += (*Uf)( sym->old_particles + i, sym->old_particles + j);
        }
    }

    return K + U;
}


void print_sym( VernelSimulation* sym, double time, double (*Uf)(Particle*, Particle*) ) {
    printf("%5.2f, ", time);
    for (int i = 0; i < sym->n_particles; i++) {
        particle_print(sym->old_particles+i, "{pos}, {vel}, ");
    }
    printf("% .3e\n", calc_nrg(sym, Uf));
}


void force_test( void ) {

    // int particles   = 1;
    // double mass     = 1;
    double side_len = 1000;
    // double init_sq  = 0;
    // int seed        = 874512;
    // double sigma    = 1;
    double dt       = 0.00001;
    double T        = 40;

    Particle ps[2] = {
        {0, 1, {{ 1,0,0}}, {{0, .1,0}}},
        {1, 1, {{0,0,0}}, {{0,0,0}}}
    };

    Particle n[2] = {0};
    VernelSimulation sym = {2, side_len, ps, n};

    for ( double t = 0; t < T; t+= dt ) {

        if ( fmod(t, T/30) < dt) { print_sym(&sym, t, get_pot_nrg_grav); }

        step_all_vernel( &sym, c_grav, dt);
    }

    print_sym(&sym, T, get_pot_nrg_grav);
}

