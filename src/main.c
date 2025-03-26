#include <stdio.h>

// #include <gsl/gsl_matrix.h>
// #include "wave_func/wave_func.h"
#include "runge_kutta/star_ex.h"

int main() {

    // calculate_r2();

    // gsl_matrix* M = gsl_matrix_alloc(5, 3);

    // gsl_matrix_set_zero(M);

    // for( size_t i = 0; i < M->size1; i++ ) {
    //     for( size_t j = 0; j < M->size2; j++ ) {
    //         printf("%f, ", gsl_matrix_get(M, i, j));
    //     }
    //     printf("\n");
    // }

    calculate_star_param();

    return 0;
}

