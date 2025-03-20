#ifndef __OPTION_H__
#define __OPTION_H__

#include <stdbool.h>

typedef struct Option {
    double is_some;
    double value;
} Option;

static const Option None = {false, 0};
Option Some(double value);

#endif//__OPTION_H__