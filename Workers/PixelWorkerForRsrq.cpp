#include "PixelWorkerForRsrq.h"
#include "Core/PixelXY.h"
#include "Common/Units.h"
#include <cmath>

std::mutex PixelWorkerForRsrq::mutex;

double PixelWorkerForRsrq::calculate(double rssi, double rsrp, int numberOfPrb ,PixelXY pixel, Rsrq& rsrq)
{
    double rsrqLvl = numberOfPrb * rsrp / rssi; //[W]
    double rsrqLvlIndB = WatTodB(rsrqLvl);

    if(!std::isinf(rsrqLvlIndB))
    {
        std::pair<PixelXY,double> pair = std::make_pair(pixel, rsrqLvlIndB);
        std::unique_lock<std::mutex> lock(mutex);
        rsrq.push_back(pair);
    }
    return rsrqLvl;
}
