#include <stdio.h>
#include "integral/integral.h"
#include <math.h>


double sin2(double x) { 
    double f = sin(2*x);
    return f*f;
}


int main() {

    double I = intt(0, 1, sin2, 200);

    printf("%e\n", I);

    return 0;
}