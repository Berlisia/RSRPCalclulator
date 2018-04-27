#pragma once
#include <thread>
#include "DataProvider.h"

class PixelXY;

class PixelWorkerForSNIR
{
public:
    double calculate(double rsrqLvl, PixelXY pixel, Snir &snir);

private:
    static std::mutex mutex;
};
