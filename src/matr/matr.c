#include "matr.h"

#include <memory.h>


vec3 vvadd( vec3 a, vec3 b) {
    
    vec3 c = {{ a.o[0] + b.o[0], a.o[1] + b.o[1], a.o[2] + b.o[2] }};

    return c;
};


mat2x2 mfrom( double arr[4] ) {
    mat2x2 M = {{ arr[0], arr[1], arr[2], arr[3] }};

    return M;
};

mat2x2 mmmult( mat2x2 A, mat2x2 B ){

    // double m0 = (A.o[0] + A.o[3]) * (B.o[0] + B.o[3]); 
    // double m1 = (A.o[2] + A.o[3]) * B.o[0];  
    // double m2 = A.o[0] * (B.o[1] - B.o[3]); 
    // double m3 = A.o[3] * (B.o[3] - B.o[0]);  
    // double m4 = (A.o[0] + A.o[1]) * B.o[3];  
    // double m5 = (A.o[2] - A.o[0]) * (B.o[0] + B.o[1]);  
    // double m6 = (A.o[1] - A.o[3]) * (B.o[2] + B.o[3]);

    // return mfrom({m0 + m3 - m4 + m6, m2 + m4, m1 + m3, m0 - m1 + m2 + m5})

    double a[4] = {
        A.o[0]*B.o[0] + A.o[1]*B.o[2], A.o[0]*B.o[1] + A.o[1]*B.o[3], 
        A.o[2]*B.o[0] + A.o[3]*B.o[2], A.o[2]*B.o[1] + A.o[3]*B.o[3] 
    };

    return mfrom(a);

}

vec2 mvmult( mat2x2 M, vec2 v ) {
    double v1q = v.a * M.o[0] + v.b * M.o[1];
    double v1p = v.a * M.o[2] + v.b * M.o[3];

    vec2 v1 = {v1q, v1p};

    return v1;
};

mat2x2 cmmult( double c, mat2x2 M) {
    mat2x2 M1 = {{M.o[0] * c, M.o[1] * c, M.o[2] * c, M.o[3] * c }};

    return M1;
};

vec2 cvmult( double c, vec2 v )
{
    vec2 v1 = {v.a * c, v.b * c};

    return v1;
};

double det( mat2x2 M ) { return M.o[0] * M.o[3] - M.o[1] * M.o[2]; }

mat2x2 inv( mat2x2 M ) {

    mat2x2 M1 = {{M.o[3], -M.o[1], -M.o[2], M.o[0]}};

    return cmmult( 1/ det(M), M1);
}