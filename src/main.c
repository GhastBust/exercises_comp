#include <stdio.h>
#include <math.h>
#include "integral/integral.h"
#include "output/output.h"


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


int main() {


    delete_and_open();
    next_chapter("Capitolo 1", 'a');
    next_sub();
    next_sub();
    next_sub();
    next_sub();
    next_chapter("CCAP 2", 'i');
    next_sub();
    next_sub();
    next_sub();


    // double I;

    // I = intt(0.0, 1.0, sin2, 200);
    // printf("a = %e\n", I);

    // I = intt(0.0, 1.0, x2sin2, 200);
    // printf("b = %e\n", I);

    // I = intt(0.0, 1.0, e05, 200);
    // printf("c = %e\n", 2-I);

    // I = intt(0.0, 1.0, x2e05, 200);
    // printf("d = %e\n", 16-I);

    return 0;
}