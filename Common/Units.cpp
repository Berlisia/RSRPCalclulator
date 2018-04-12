#include <cmath>
#include "Units.h"

double dBmToW(double dBm)
{
    return std::pow(10, dBm/10)/1000;
}

double WatTodB(double wat)
{
    return std::log10(wat)*10;
}
