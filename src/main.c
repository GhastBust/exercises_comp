#include <stdio.h>
#include <math.h>
#include "intt/trap/trap.h"
#include "intt/simpson/simpson.h"
#include "output/output.h"
#include "vec/vec.h"

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

// void print_integrals() {

//     void* file = delete_and_open();

//     next_chapter("Integrali con il metodo del trapezio:", 'a');
//     double I;

//     next_sub();
//     I = int_trap(0.0, 1.0, sin2, 200);
//     fprintf(file, "trap: %e,\t", I);
//     I = int_simp(0.0, 1.0, sin2, 200);
//     fprintf(file, "simps: %e", I);

//     next_sub();
//     I = int_trap(0.0, 1.0, x2sin2, 200);
//     fprintf(file, "trap: %e,\t", I);
//     I = int_simp(0.0, 1.0, x2sin2, 200);
//     fprintf(file, "simps: %e", I);

//     next_sub();
//     I = int_trap(0.0, 1.0, e05, 200);
//     fprintf(file, "trap: %e,\t", 2-I);
//     I = int_simp(0.0, 1.0, e05, 200);
//     fprintf(file, "simps: %e", 2-I);

//     next_sub();
//     I = int_trap(0.0, 1.0, x2e05, 200);
//     fprintf(file, "trap: %e,\t", 16-I);
//     I = int_simp(0.0, 1.0, x2e05, 200);
//     fprintf(file, "simps: %e", 16-I);
// }


const double R = 1.93;

// const double Mev_J = 1.60218e-13;
const double Mn = 939.565;
const double Mp = 938.272;
const double c = 299792458;
const double uc2 = Mn*Mp/(Mn+Mp);
const double hc = 197.327;
const double V0 = 38.5;
const double lambda = hc*hc/2/uc2/R/R;
const double v = V0 / lambda;

double f2(double x) {
    return 1/tan(sqrt(v-x));
}

double f1(double x) {
    return -sqrt(x/(v-x));
}

int main() {

    csv_open_write("ctn_sqrt.csv");

    struct Vec a = linspacee (0, v, 2000);
    double x;
    
    for (int i = 0; i < a.len; i++) {
        x = a.array[i];
        csv_write(x);
        csv_write(f1(x));
        csv_write(f2(x));
        csv_new_line();
    }

    csv_close();

    return 0;
}

