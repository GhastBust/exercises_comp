#include "ex_06.h"


#include <math.h>

#include "../../vel-ver/vel-ver.h"
#include "../../output/output.h"

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
    double h = 1e-4;

    csv_open_write("data/harmonic_vel-ver.csv");

    for (double t = 0; t < T; t += h) {

        x = step_vel_ver(x, harmonic_pot, 1, h);

        csv_write(x.a);
        csv_write(x.b);
        csv_write(harmonic_herm(x));
        csv_new_line();

    }

    csv_close();
}