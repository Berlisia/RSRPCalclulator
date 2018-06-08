#include "PixelWorkerForSNIR.h"
#include "Core/PixelXY.h"
#include "Common/FrequencyBands.h"
#include "Common/Units.h"
#include <cmath>
#include <QDebug>

std::mutex PixelWorkerForSNIR::mutex;

extern const double numberOfSubcarriersInRB;
extern const double subcarrierActivityFactor;

double PixelWorkerForSNIR::calculate(double rsrq, PixelXY pixel, Snir& snir)
{
    double snirlvl = 1 / ((1 / (numberOfSubcarriersInRB * rsrq) - subcarrierActivityFactor));
    double snirlvlIndB = WatTodB(snirlvl);
    if(!std::isinf(snirlvlIndB))
    {
        std::pair<PixelXY,double> pair = std::make_pair(pixel, snirlvlIndB);
        std::unique_lock<std::mutex> lock(mutex);
        snir.push_back(pair);
    }
    return snirlvlIndB;
}
