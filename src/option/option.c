#include "option.h"

Option Some(double value) {
    return (Option){true, value};
} 