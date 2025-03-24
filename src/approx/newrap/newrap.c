#include "newrap.h"

#include <math.h>

static const double R = 1.93;
static const double Mn = 939.565;
static const double Mp = 938.272;
static const double uc2 = Mn*Mp/(Mn+Mp);
static const double hc = 197.327;
static const double lambda = hc*hc/2/uc2/R/R;

double der(double (*f)(double), double x, double h) {

    const double f1 = (*f)(x-h);
    const double f2 = (*f)(x+h);

    return (f2-f1)/2/h;
};

Option newrap(double (*f)(double), double x, double e, clock_t start, Vec* results ){

    if (clock() - start >= 1 * CLOCKS_PER_SEC ) {return None;}
    if (fabs(x) > 1e20) return None;

    const double x1 = x - (*f)(x)/ der(f, x, e*1e-3);

    vappend(results, x1*lambda);

    if (fabs(x1-x) < e) return Some(x1);

    return newrap(f, x1, e, start, results);
};