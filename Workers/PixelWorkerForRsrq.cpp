#include "PixelWorkerForRsrq.h"
#include "Core/PixelXY.h"
#include "Common/Units.h"

std::mutex PixelWorkerForRsrq::mutex;

PixelWorkerForRsrq::PixelWorkerForRsrq()
{
}

double PixelWorkerForRsrq::calculate(double rssi, double rsrp, int numberOfPrb ,PixelXY pixel, Rsrq& rsrq)
{
    double rsrqLvl = WatTodB(numberOfPrb) + rsrp - rssi;
    std::pair<PixelXY,double> pair = std::make_pair(pixel, rsrqLvl);

    if(!std::isinf(rsrqLvl))
    {
        std::unique_lock<std::mutex> lock(mutex);
        rsrq.push_back(pair);
    }
    return rsrqLvl;
}
