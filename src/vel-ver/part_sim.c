#include "vel-ver.h"

#include <malloc.h>
#include <math.h>

typedef struct VernelSimulation {
    int     n_particles;

    vec3*       forces;
    Particle*   old_particles;
    Particle*   new_particles;

} VernelSimulation;


inline double Pdistance2( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return v3norm2(temp);
};

inline vec3 direct( const Particle* a, const Particle* b ) {
    vec3 temp = vvdiff(&a->pos, &b->pos);
    return cv3mult(1/sqrt(v3norm2(temp)), &temp);
};

double int_pow( double base, int exp ) {

    if (exp < 0) {
        base = 1/base;
        exp = -exp;
    }

    if (exp == 0) {return 1;}

    if ( exp == 2 ) { return base * base;}

    if (exp % 2 == 0) {
        double half_pow = int_pow(base, exp/2);
        return half_pow * half_pow;
    } else {
        double one_minus_pow = int_pow(base, exp-1);
        return one_minus_pow * base;
    }
}


inline vec3 get_force_between( const Particle* a, const Particle* b ) {

    double r = sqrt( Pdistance2(a, b) );

    double r6 = int_pow(r, 6);
    double r13 = r6 * r6 * r;

    double force = 6 * (r6 - 2) / r13;

    vec3 force3 = direct(a, b);
    
    force3 = cv3mult(force, &force3);

    return force3;
};


VernelSimulation setup_simulation( size_t num_particles, double radius ) {};




double LJ_pot( double r ) {

    double sigma_r_6 =  int_pow( sigma/r, 3);
    sigma_r_6 *= sigma_r_6;

    return 4 *epsilon *sigma_r_6 *(sigma_r_6 - 1);
}


double potential_U( void* p_simulation, const vec3* part ) {

    VernelSimulation* simulation = (VernelSimulation*) p_simulation; //! molto unsafe, ma unico modo di procedere


}

