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

double f1f2(double x) {
    return f1(x) - f2(x);
}

void graph_and_write(char* name_of_file) {

    csv_open_write(name_of_file);

    Vec a = linspacee (0, v, 4000);
    double x;

    for (unsigned i = 0; i < a.len; i++) {
        x = a.ptr[i];
        csv_write(x);
        csv_write(f1(x));
        csv_write(f2(x));
        csv_new_line();
    }
    
    csv_close();
}

void write_vec_to_file(char* name_of_file, Vec* vec) {
    csv_open_write(name_of_file);
    
        Vec a = *vec;
        double x;
    
        for (unsigned i = 0; i < a.len; i++) {
            x = a.ptr[i];
            csv_write(x);
            csv_new_line();
        }
    
    csv_close();
};


void bis(void) {

    Vec vv = vcreate();

    vappend(&vv, 0);
    vappend(&vv, v);

    Option ress = bisect(f1f2, 0.0, v, 1e-10, &vv);

    if (!ress.is_some) {
        printf("La bisezione non ha prodotto risultati.\n");
        return;
    }

    double res = ress.value;

    write_vec_to_file("bisection.csv", &vv);
    

    printf("Il risultato della bisezione è:\n");
    printf("%.10E\n", res);

    return;
}

void nr(void) {

    const double x0 = v-0.000001;

    Vec vv = vcreate();
    vappend(&vv, x0);

    Option ress = newrap(f1f2, x0, 1e-10, clock(), &vv);

    if (!ress.is_some) {
        printf("Newton-rapson non ha prodotto risultati.\n");
        return;
    }

    double res = ress.value;

    write_vec_to_file("newton-rapson.csv", &vv);

    for (unsigned i = 0; i < vv.len; i++) {

    }

    printf("Il risultato della newton-rapson è:\n");
    printf("%.10E\n", res);

    return;
}

