#include "matr.h"

#include <memory.h>
#include <stdarg.h>

vec3 vminus(vec3 v)
{
    vec3 new_v = {0};

    for ( int i = 0; i < 3; i++) {
        new_v.o[i] = -v.o[i];
    }

    return new_v;
}

double v3norm2(vec3 v)
{
    double norm = 0;

    for( int i = 0; i < 3; i++ ) {
        norm += v.o[i] * v.o[i];
    }

    return norm;
};

vec2    vadd ( vec2 a, vec2 b) {
    return (vec2){a.a+b.a, a.b+b.b};
}

vec3 vvadd( const vec3* a, const vec3* b) {
    
    vec3 new_v = {{0}};

    for (int i = 0; i < 3; i++) {
        new_v.o[i] = a->o[i] + b->o[i];
    }

    return new_v;
};


vec3 mvvadd( int count,... ) {

    vec3 result = {0};

    va_list args;
    va_start(args, count);
 
    for (int i = 0; i < count; ++i) {
        result = vvadd( &result, va_arg(args, vec3*) );
    }
 
    va_end(args);
    return result;

}


vec3 vvdiff( const vec3* a, const vec3* b) {

    vec3 new_v = {{0}};

    for (int i = 0; i < 3; i++) {
        new_v.o[i] = a->o[i] - b->o[i];
    }

    return new_v;
};

double vvscal( vec3 a, vec3 b) {

    double prod = 0;

    for (int i = 0; i < 3; i++) {
        prod += a.o[i] * b.o[i];
    }

    return prod;
}

vec3 cv3mult(double c, const vec3* v)
{
    vec3 new_v = {{0}};

    for (int i = 0; i < 3; i++) {
        new_v.o[i] = c * v->o[i];
    }

    return new_v;
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