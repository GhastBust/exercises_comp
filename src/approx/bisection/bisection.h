#ifndef __BISECTION_H__
#define __BISECTION_H__


#include "../../option/option.h"

Option bisect(double (*f)(double), double a, double b, double e);



#endif//__BISECTION_H__
