#ifndef __NEWRAP_H__
#define __NEWRAP_H__

#include <time.h>

#include "../../option/option.h"

double der(double (*f)(double), double x, double h);

Option newrap(double (*f)(double), double x, double e, clock_t start);

#endif//__NEWRAP_H__
