#include <stdio.h>
#include <time.h>
#include <math.h>

#include "approx/approx.h"
#include "wave_func/wave_func.h"

#include "approx/fconst.h"


// void approx_bis_new_rap() {

//     clock_t start;
//     clock_t end;
    
//     start = clock();
//     bis();
//     end = clock();
    
//     printf("Il metodo di bisezione ci ha messo %ld us\n", (end-start));
    
//     start = clock();
//     nr();
//     end = clock();
    
//     printf("Il metodo di newton-rapson ci ha messo %ld us\n", (end-start));

//     return;
// }



int main() {

    double k = sqrt(2*uc2*(V0 - E)/hc/hc);
    double q = sqrt(-2*uc2*E/hc/hc);
    double A = 100;
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

    return 0;
}

