#include "approx.h"

#include <math.h>
#include <stdio.h>

#include "../output/output.h"
#include "../vec/vec.h"
#include "../option/option.h"
#include "bisection/bisection.h"
#include "newrap/newrap.h"


const double R = 1.93;
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

void graph_and_write(char* name_of_file) {
    csv_open_write(name_of_file);

struct Vec a = linspacee (0, v, 4000);
double x;

for (int i = 0; i < a.len; i++) {
    x = a.array[i];
    csv_write(x);
    csv_write(f1(x));
    csv_write(f2(x));
    csv_new_line();
}

csv_close();
}

double f1f2(double x) {
    return f1(x) - f2(x);
}

void bis(void) {

    Option ress = bisect(f1f2, 0.0, v, 0.000001);

    if (!ress.is_some) {
        printf("La bisezione non ha prodotto risultati.\n");
    }

    double res = ress.value;

    printf("Il risultato della bisezione è:\n");
    printf("%E\n", res);

    return;
}

void nr(void) {

    Option ress = newrap(f1f2, v-0.000001, 0.000001, clock());

    if (!ress.is_some) {
        printf("Newton-rapson non ha prodotto risultati.\n");
    }

    double res = ress.value;

    printf("Il risultato della newton-rapson è:\n");
    printf("%E\n", res);

    return;
}

