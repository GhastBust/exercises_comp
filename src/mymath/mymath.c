#include "mymath.h"

double int_pow( double base, int exp ) {

    if (exp < 0) {
        base = 1/base;
        exp = -exp;
    }

    if (exp == 0) {return 1;}

    if ( exp == 2 ) { return base * base;}

    if (exp % 2 == 0) {
        double half_pow = int_pow(base, exp/2);
        return half_pow * half_pow;
    } else {
        double one_minus_pow = int_pow(base, exp-1);
        return one_minus_pow * base;
    }
}