#pragma once
#include <thread>
#include "DataProvider.h"

class PixelXY;

class PixelWorkerForRsrq
{
public:

    double calculate(double rssi, double rsrp, int numberOfPrb , PixelXY pixel, Rsrq& rsrq);
private:
    static std::mutex mutex;
};
