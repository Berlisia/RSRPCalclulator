#include "PixelWorkerForSNIR.h"
#include "Core/PixelXY.h"
std::mutex PixelWorkerForSNIR::mutex;

PixelWorkerForSNIR::PixelWorkerForSNIR()
{
}

void PixelWorkerForSNIR::calculate(double intLvl, double signalLvl, PixelXY pixel, Snir& snir)
{
    double snirLvl = signalLvl - intLvl;
    std::pair<PixelXY,double> pair = std::make_pair(pixel, snirLvl);

    if(!std::isinf(snirLvl))
    {
        std::unique_lock<std::mutex> lock(mutex);
        snir.push_back(pair);
    }
}
