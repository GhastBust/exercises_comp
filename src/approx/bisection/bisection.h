#ifndef __BISECTION_H__
#define __BISECTION_H__

#include "../../option/option.h"
#include "../../vec/vec.h"

Option bisect(double (*f)(double), double a, double b, double e, Vec* results);

#endif//__BISECTION_H__
