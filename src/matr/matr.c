#include "matr.h"


vec2 mvmult( mat2x2 M, vec2 v ) {
    double v1q = v.q * M.a + v.p * M.b;
    double v1p = v.q * M.c + v.p * M.d;

    vec2 v1 = {v1q, v1p};

    return v1;
};

mat2x2 cmmult( double c, mat2x2 M) {
    mat2x2 M1 = {M.a * c, M.b * c, M.c * c, M.d * c};

    return M1;
};

vec2 cvmult( double c, vec2 v )
{
    vec2 v1 = {v.q * c, v.p * c};

    return v1;
};

double det( mat2x2 M ) { return M.a * M.d - M.b * M.c; }

mat2x2 inv( mat2x2 M ) {

    mat2x2 M1 = {M.d, -M.b, -M.c, M.a};

    return cmmult( 1/ det(M), M1);
}