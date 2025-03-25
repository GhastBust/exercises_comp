#ifndef __SIMPSON_H__
#define __SIMPSON_H__

#include <malloc.h>

double int_simp(double a, double b, double (*f)(double), int n);

#endif //__SIMPSON_H__