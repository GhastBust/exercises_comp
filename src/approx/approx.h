#ifndef __APPROX_H__
#define __APPROX_H__

#include <time.h>
#include <stdio.h>

#include "../vec/vec.h"

double f2(double x);
double f1(double x);
double f1f2(double x);

void graph_and_write(char* name_of_file);
void write_vec_to_file(char* name_of_file, Vec* vec);

void bis(void);
void nr(void);

void approx_bis_new_rap();

#endif//__APPROX_H__