#include "ex_02.h"
#include "fconst.h"

#include <math.h>
#include <stdio.h>

#include "../../output/output.h"
#include "../../vec/vec.h"
#include "../../option/option.h"
#include "../../approx/bisection/bisection.h"
#include "../../approx/newrap/newrap.h"
#include "../../intt/simpson/simpson.h"


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

    vec a = linspacee (0, v, 4000);
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

void write_vec_to_file(char* name_of_file, vec* v) {
    csv_open_write(name_of_file);
    
        vec a = *v;
        double x;
    
        for (unsigned i = 0; i < a.len; i++) {
            x = a.ptr[i];
            csv_write(x);
            csv_new_line();
        }
    
    csv_close();
};


void bis(void) {

    vec vv = vcreate();

    vappend(&vv, 0);
    vappend(&vv, v);

    Option ress = bisect(f1f2, 0, v, 1e-12, &vv);

    if (!ress.is_some) {
        printf("La bisezione non ha prodotto risultati.\n");
        return;
    }

    double res = ress.value;

    write_vec_to_file("data/bisection.csv", &vv);
    

    printf("Il risultato della bisezione è:\n");
    printf("%.13E\n", res*lambda);

    return;
}

void nr(void) {

    const double x0 = v-0.000001;

    vec vv = vcreate();
    vappend(&vv, x0);

    Option ress = newrap(f1f2, x0, 1e-12, clock(), &vv);

    if (!ress.is_some) {
        printf("Newton-rapson non ha prodotto risultati.\n");
        return;
    }

    double res = ress.value;

    write_vec_to_file("data/newton-rapson.csv", &vv);

    for (unsigned i = 0; i < vv.len; i++) {

    }

    printf("Il risultato della newton-rapson è:\n");
    printf("%.13E\n", res*lambda);

    return;
}

void approx_bis_new_rap() {

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

    return;
}


// double k = sqrt(2*uc2*(V0 - E)/hc/hc);
// double q = sqrt(2*uc2*E/hc/hc);
// double A = 1;
// double B = A * sin(k*R) / exp(-q*R);
// double remainder1 = B*B/4/q/q/q;
// double remainder2 = B*B/2/q;

const double k = 9.366109318822E-01;
const double q = 2.260923880842E-01;
const double A = 5.611000000000E-01;
const double B = 8.438199718631E-01;
const double remainder1 = 1.540216550712E+01;
const double remainder2 = 1.574648644629E+00;

double wave1(double r) { return A * sin(k*r); }
double wave2(double r) { return B * exp(-q*r); }


double r2_u2(double r) {
    double r2 = r*r;

    double w1 = wave1(r);
    double w2 = wave2(r);

    w1 *= w1;
    w2 *= w2;

    return r2 * (w1-w2);
}

double u2(double r) {
    double w1 = wave1(r);
    double w2 = wave2(r);

    w1 *= w1;
    w2 *= w2;

    return w1 - w2;
}

double mean_r2() {

    double numerator = remainder1 + int_simp(0, R, r2_u2, 200000);

    double denominator = remainder2 + int_simp(0, R, u2, 200000);

    return numerator / denominator;

}

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