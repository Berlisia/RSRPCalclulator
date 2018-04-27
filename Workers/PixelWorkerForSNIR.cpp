#include "PixelWorkerForSNIR.h"
#include "Core/PixelXY.h"
#include "Common/FrequencyBands.h"
#include "Common/Units.h"
#include <cmath>

std::mutex PixelWorkerForSNIR::mutex;

double PixelWorkerForSNIR::calculate(double rsrq, PixelXY pixel, Snir& snir)
{
    double snirlvl = subcarrierActivityFactor / ((1 / (numberOfSubcarriersInRB * rsrq) - subcarrierActivityFactor));
    double snirlvlIndB = WatTodB(snirlvl);
    if(!std::isinf(snirlvlIndB))
    {
        std::pair<PixelXY,double> pair = std::make_pair(pixel, snirlvlIndB);
        std::unique_lock<std::mutex> lock(mutex);
        snir.push_back(pair);
    }
    return snirlvlIndB;
}
