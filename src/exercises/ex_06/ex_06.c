#include "ex_06.h"

#include <math.h>
#include <malloc.h>

#include "../../vel-ver/vel-ver.h"
#include "../../output/output.h"

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


void calc_LJ_fluid_sim( void ) {

    int particles   = 100;
    double mass     = 1;
    double side_len = 10;
    int seed        = 12345678;
    double sigma    = 1;
    double dt       = 0.01;

    VernelSimulation sym = init_simulation( particles, mass, side_len, seed );

    for ( double t = 0; t < 20; t+= dt ) {

        for ( int i = 0; i < particles; i++) {
            Particle* p = sym.old_particles + i;
            Particle new_p = step_vernel_vec3_cforce(p, &sym, LJ_force, dt);
    
            sym.new_particles[i] = new_p;
        }

        swap_old_new(&sym);
    }

    
    
}