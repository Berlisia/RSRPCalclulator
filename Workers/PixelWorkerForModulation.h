#pragma once
#include <thread>
#include "DataProvider.h"

class PixelXY;

class PixelWorkerForModulation
{
public:
    PixelWorkerForModulation();

    void calculate(PixelXY pixel, ModulationScheme &snir);
private:
    static std::mutex mutex;
};
