#include <stdio.h>
#include <math.h>
#include "intt/trap/trap.h"
#include "intt/simpson/simpson.h"
#include "output/output.h"

#include "diag/diag.h"


double sin2(double x) { 
    double f = sin(2*x);
    return f*f;
}

double x2sin2(double x) {
    double f = x*sin(2*x);
    return f*f;
}

double e05( double x) {
    return exp(-.5 * x);
}

double x2e05( double x) {
    return x*x*e05(x);
}

void print_integrals() {

    void* file = delete_and_open();

    next_chapter("Integrali con il metodo del trapezio:", 'a');
    double I;

    next_sub();
    I = int_trap(0.0, 1.0, sin2, 200);
    fprintf(file, "trap: %e,\t", I);
    I = int_simp(0.0, 1.0, sin2, 200);
    fprintf(file, "simps: %e", I);

    next_sub();
    I = int_trap(0.0, 1.0, x2sin2, 200);
    fprintf(file, "trap: %e,\t", I);
    I = int_simp(0.0, 1.0, x2sin2, 200);
    fprintf(file, "simps: %e", I);

    next_sub();
    I = int_trap(0.0, 1.0, e05, 200);
    fprintf(file, "trap: %e,\t", 2-I);
    I = int_simp(0.0, 1.0, e05, 200);
    fprintf(file, "simps: %e", 2-I);

    next_sub();
    I = int_trap(0.0, 1.0, x2e05, 200);
    fprintf(file, "trap: %e,\t", 16-I);
    I = int_simp(0.0, 1.0, x2e05, 200);
    fprintf(file, "simps: %e", 16-I);
}


int main() {

    info("Questa è un info");
    warning("Questo è un warning");
    cricical("Errore critico");

    return 0;
}