#include "vel-ver.h"

#include "../approx/approx.h"


double calc_new_pos( vec2 x, double (*U) (double), double m, double h ) {

    return x.a + x.b * h + h *h /2 /m *der(U, x.a, h/10);
    
}

double calc_new_vel( vec2 x, double new_pos, double (*U) (double), double m, double h ) {

    #define F(y) (- der(U, (y), h/10) )

    return x.b + h /2 /m *( F(x.a) + F(new_pos) );
}

vec2 step_vel_ver( vec2 x, double (*U) (double), double m, double h ) {

    double new_pos = calc_new_pos(x, U, m, h);

    double new_vel = calc_new_vel(x, new_pos, U, m, h);

    return (vec2){ new_pos, new_vel};

}