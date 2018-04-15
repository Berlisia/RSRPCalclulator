#include "PixelWorkerForSNIR.h"
#include "Core/PixelXY.h"
#include "Common/FrequencyBands.h"
#include "Common/Units.h"
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
    double snirlvlIndB = WatTodB(snirLvl);
    if(!std::isinf(snirLvl))
    {
        std::pair<PixelXY,double> pair = std::make_pair(pixel, snirlvlIndB);
        std::unique_lock<std::mutex> lock(mutex);
        snir.push_back(pair);
    }
    return snirlvlIndB;
}
