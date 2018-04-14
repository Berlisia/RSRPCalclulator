#include "PixelWorkerForSNIR.h"
#include "Core/PixelXY.h"
#include "Common/FrequencyBands.h"
#include <cmath>
const double numberOfSubcarriersInRB = 12.0;
const double subcarrierActivityFactor = 5/6;

std::mutex PixelWorkerForSNIR::mutex;

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
