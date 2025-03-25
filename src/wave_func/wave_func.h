#ifndef __WAVE_FUNC_H__
#define __WAVE_FUNC_H__

#include <stdio.h>
#include <math.h>

#include "../approx/approx.h"

#include "../approx/fconst.h"
#include "../intt/simpson/simpson.h"

// double wave_func_u(double r);
double mean_r2();

void calculate_r2() {
    double k = sqrt(2*uc2*(V0 + E)/hc/hc);
    double q = sqrt(-2*uc2*E/hc/hc);
    double A = 0.5611;
    double B = A * sin(k*R) / exp(-q*R);
    double remainder1 = B*B/4/q/q/q;
    double remainder2 = B*B/2/q;

    printf("k = %.12E\n", k);
    printf("q = %.12E\n", q);
    printf("A = %.12E\n", A);
    printf("B = %.12E\n", B);
    printf("remainder1 = %.12E\n", remainder1);
    printf("remainder2 = %.12E\n", remainder2);

    printf("<r²> = %.10E\n", mean_r2());
}

#endif//__WAVE_FUNC_H__
