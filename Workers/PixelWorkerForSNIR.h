#pragma once
#include <thread>
#include "DataProvider.h"

class PixelXY;

class PixelWorkerForSNIR
{
public:
    PixelWorkerForSNIR();

    void calculate(double intLvl, double signalLvl, PixelXY pixel, Snir &snir);
private:
    static std::mutex mutex;
};
