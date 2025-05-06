#include "ex_06.h"

#include <math.h>
#include <malloc.h>

#include "test_forces.h"
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

    double temp = 0;

    for (size_t i = 0; i < sym->n_particles; i++) {
        temp += get_kin_nrg(sym->old_particles + i);
    }

    return temp / 3 / sym->n_particles;
}


vec3 LJ_force( const Particle* a, const Particle* b ) {

    double r = sqrt( particle_distance2(a, b) );

    double r6 = int_pow(r, 6);
    double r13 = r6 * r6 * r;

    double force = 6 * (r6 - 2) / r13;

    vec3 force3 = particle_direction_versor(a, b);
    
    force3 = cv3mult(force, &force3);

    return force3;
};


// vec3 LJ_force( const Particle* part, const void* vp_system ) {
        
//     const VernelSimulation* sym = (VernelSimulation*) vp_system;

//     vec3 current_force;
//     vec3 force_on_particle = {0};

//     for (int i = 0; i < sym->n_particles; i++) {
        
//         if ( i == part->id ) {continue;}

//         Particle mirrored = mirror_particle(part, sym->side_len, sym->old_particles + i);

//         current_force = get_force_between(part, &mirrored);

//         force_on_particle = vvadd(&force_on_particle, &current_force);
//     }

//     return force_on_particle;
// }

// void calc_LJ_fluid_sim( void ) {

//     double starting_temp = 1.1;
//     int particles   = 1000;
//     double mass     = 1;
//     double side_len = 10;
//     double init_sq  = 1;
//     int seed        = 65412752;
//     int cycles      = 50000;
//     double dt       = 0.001;
    
//     double T        = cycles * dt;
//     double sigma    = sqrt(starting_temp / mass);

    // VernelSimulation sym = init_simulation( particles, mass, side_len, init_sq, seed, sigma);

//     for ( double t = 0; t < T; t+= dt ) {


//         printf("%f\n", calc_temp(&sym));

//         calc_nrg(&sym, zero_c_pot, LJ_force);

//         step_all_vernel( &sym, zero_frc, dt);
//     }
// }
