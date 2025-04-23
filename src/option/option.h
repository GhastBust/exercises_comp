#ifndef __OPTION_H__
#define __OPTION_H__

#include <stdbool.h>

typedef struct Option {
    bool is_some;
    double value;
} Option;

static const Option None = {false, 0};
Option Some(double value);

typedef struct IOption
{
    bool is_some;
    int value;
} IOption;

static const IOption INone = {false, 0};
IOption ISome(int value);


#endif//__OPTION_H__