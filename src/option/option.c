#include "option.h"

Option Some(double value) {
    return (Option){true, value};
}
IOption ISome(int value)
{
    return (IOption){true, value};
    
}
