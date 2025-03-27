#include "runge_kutta.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

vec3 next_rk_step( vec3 v, double(*f)(vec3), double(*g)(vec3), double h ) {

    vec3 add;
    
    double t_next = v.o[0] + h;

    double k1 = h * (*f)(v);
    double l1 = h * (*g)(v);

    add = (vec3){{ h/2, k1/2, l1/2 }};

    double k2 = h * (*f)(vvadd(v, add));
    double l2 = h * (*g)(vvadd(v, add));

    add = (vec3){{ h/2, k2/2, l2/2 }};

    double k3 = h * (*f)(vvadd(v, add));
    double l3 = h * (*g)(vvadd(v, add));

    add = (vec3){{ h, k3, l3 }};

    double k4 = h * (*f)(vvadd(v, add));
    double l4 = h * (*g)(vvadd(v, add));

    double x_next = v.o[1] + 1.0 /6 *( k1 + 2*k2 + 2*k3 + k4 );
    double y_next = v.o[2] + 1.0 /6 *( l1 + 2*l2 + 2*l3 + l4 );

    vec3 v_next = {{ t_next, x_next, y_next }};

    return v_next;

};

txyvec  exe_runge_kutta( vec3 initial, double final, double(*f)(vec3), double(*g)(vec3), double h ) {

    // int steps = ceil((final - initial.o[0]) / h) + 1;

    txyvec results = { vcreate(), vcreate(), vcreate() };
    vec3 i_txy = initial;

    vappend( &results.t, i_txy.o[0] );
    vappend( &results.x, i_txy.o[1] );
    vappend( &results.y, i_txy.o[2] );

    while (i_txy.o[0] < final ) {
        i_txy = next_rk_step(i_txy, f, g, h);

        vappend( &results.t, i_txy.o[0] );
        vappend( &results.x, i_txy.o[1] );
        vappend( &results.y, i_txy.o[2] );
    }

    return results;
};

void  vvvprint( txyvec v, char* format, char* sep ) {

    int minn = fmin(v.t.len, v.x.len);
    minn = fmin(minn, v.y.len);

    if ( sep == NULL ) {
        for (int i = 0; i < minn; i++){ 
            printf(format, v.t.ptr[i], v.x.ptr[i], v.y.ptr[i]);
            printf("\n");
        }
        return;
    }

    for (int i = 0; i < minn; i++){

        printf(format, v.t.ptr[i]);
        printf("%s", sep);        
        printf(format, v.x.ptr[i]);
        printf("%s", sep);        
        printf(format, v.y.ptr[i]);
        printf("\n");
    }

    return;

};
