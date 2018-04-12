#include "PixelWorkerForSNIR.h"
#include "Core/PixelXY.h"
std::mutex PixelWorkerForSNIR::mutex;

namespace
{
    double numberOfSubcarriersInRB = 12.0;
    double subcarrierActivityFactor = 1.0;
}

PixelWorkerForSNIR::PixelWorkerForSNIR()
{
}

double PixelWorkerForSNIR::calculate(double rsrq, PixelXY pixel, Snir& snir)
{
    double snirLvl = 1 / ((1 / (numberOfSubcarriersInRB * rsrq) - subcarrierActivityFactor));
    std::pair<PixelXY,double> pair = std::make_pair(pixel, snirLvl);

    if(!std::isinf(snirLvl))
    {
        std::unique_lock<std::mutex> lock(mutex);
        snir.push_back(pair);
    }
    return snirLvl;
}
