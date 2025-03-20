#include <stdio.h>
#include <time.h>

#include "approx/approx.h"

int main() {

    clock_t start;
    clock_t end;

//    /* Create independent threads each of which will execute function */

    start = clock();
    bis();
    end = clock();

    printf("Il metodo di bisezione ci ha messo %ld us\n", (end-start));

    start = clock();
    nr();
    end = clock();

    printf("Il metodo di newton-rapson ci ha messo %ld us\n", (end-start));


    return 0;
}

