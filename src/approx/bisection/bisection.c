#include "bisection.h"

Option bisect(double (*f)(double), double a, double b, double e) {

    // if (clock() - start >= 1 * CLOCKS_PER_SEC) {return None;}
    
    if ((*f)(a)*(*f)(b) > 0)  {return None;}
    
    if ( (*f)(a) == 0 )    {return Some(a);}
    if ( (*f)(b) == 0 )    {return Some(b);}
    
    const double c = (a+b) / 2;
    if ( b-a < e)       {return Some(c);}

    const Option first = bisect( f, a, c, e);
    if (first.is_some) {return first;}
    
    const Option second = bisect( f, c, b, e);
    if (second.is_some) {return second;}

    return None;
};