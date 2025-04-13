#include "mymath.h"

vec3 gradient_v3( double (*f) (const vec3*), const vec3* v, const vec3* dv ) {

    vec3 res;

    double f1;
    double f2;

    vec3 dxyz[3] = {    
        (vec3) {{1, 0, 0}},
        (vec3) {{0, 1, 0}},
        (vec3) {{0, 0, 1}},
    };

    for (int i = 0; i < 3; i++) {
        dxyz[i].o[i] = dv->o[i];
    }

    for (int i = 0; i < 3; i++) {

        vec3 dif = vvdiff(v, &dxyz[i]);
        vec3 add = vvadd (v, &dxyz[i]);

        f1 = (*f)( &dif );
        f2 = (*f)( &add );
    
        res.o[i] = (f2-f1) /2 / dv->o[i];
    }

    return res;
}