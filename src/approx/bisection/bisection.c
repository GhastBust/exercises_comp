#include "bisection.h"

#include "../fconst.h"

// static const double R = 1.93;
// static const double Mn = 939.565;
// static const double Mp = 938.272;
// static const double uc2 = Mn*Mp/(Mn+Mp);
// static const double hc = 197.327;
// static const double lambda = hc*hc/2/uc2/R/R;
// // const double c = 299792458;
// // const double V0 = 38.5;
// // const double v = V0 / lambda;

Option bisect(double (*f)(double), double a, double b, double e, Vec* results) {

    if ((*f)(a)*(*f)(b) > 0)  {return None;}
    
    if ( (*f)(a) == 0 )    {return Some(a);}
    if ( (*f)(b) == 0 )    {return Some(b);}
    
    const double c = (a+b) / 2;
    
    vappend(results, c*lambda);

    if ( b-a < e)       {return Some(c);}

    const Option first = bisect( f, a, c, e, results);
    if (first.is_some) {return first;}
    
    const Option second = bisect( f, c, b, e, results);
    if (second.is_some) {return second;}

    return None;
};