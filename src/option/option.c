#include "option.h"

Option Some(double value) {
    Option o = {true, value};
    return o;
} 