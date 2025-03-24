#include <stdio.h>
#include <time.h>
#include <math.h>

#include "approx/approx.h"

int main() {

    clock_t start;
    clock_t end;

    start = clock();
    bis();
    end = clock();

    printf("Il metodo di bisezione ci ha messo %ld us\n", (end-start));

    start = clock();
    nr();
    end = clock();

    printf("Il metodo di newton-rapson ci ha messo %ld us\n", (end-start));

    // printf("%.20e\n", nextafter(1.0, 2.0)-1.0);

    return 0;
}

