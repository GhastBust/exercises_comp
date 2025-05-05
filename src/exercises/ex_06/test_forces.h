#ifndef __TEST_FORCES_H__
#define __TEST_FORCES_H__

#include <math.h>

#include "../../matr/matr.h"
#include "../../vel-ver/vel-ver.h"
#include "../../mymath/mymath.h"


void test_zero_force( void );
void test_central_grav( void );
void test_reciprocal_grav2( void );
void test_reciprocal_grav3( void );

// void force_test( void ) {

//     double side_len = 1000;
//     double dt       = 0.00001;
//     double T        = 40;

//     Particle ps[2] = {
//         {0, 1, {{ 1,0,0}}, {{0, .1,0}}},
//         {1, 1, {{0,0,0}}, {{0,0,0}}}
//     };

//     Particle n[2] = {0};
//     VernelSimulation sym = {2, side_len, ps, n};

//     for ( double t = 0; t < T; t+= dt ) {

//         if ( fmod(t, T/30) < dt) { print_sym(&sym, t, get_pot_nrg_grav); }

//         step_all_vernel( &sym, c_grav, dt);
//     }

//     print_sym(&sym, T, get_pot_nrg_grav);
// }

#endif //__TEST_FORCES_H__