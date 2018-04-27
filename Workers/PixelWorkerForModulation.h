#pragma once
#include <thread>
#include "DataProvider.h"

class PixelXY;
class PixelWorkerForSNIR;

class PixelWorkerForModulation
{
public:
    int calculate(PixelXY pixel, double snir, ModulationScheme& modulationVec);

private:
    int chooseProperCQI(double snirValue);
    static std::mutex mutex;
};
