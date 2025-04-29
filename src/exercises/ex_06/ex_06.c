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
            Particle new_p = step_vernel_vec3(p, &sym, LJ_force, dt);
    
            sym.new_particles[i] = new_p;
        }

        swap_old_new(&sym);
    }
}
