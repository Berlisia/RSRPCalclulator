#include "PixelWorkerForInterference.h"
#include "Core/PixelXY.h"
#include <algorithm>
#include <QDebug>
#include <cmath>
std::mutex PixelWorkerForInterference::mutex;

PixelWorkerForInterference::PixelWorkerForInterference(const std::vector<PrbBandAndSignalStrengeMapping> &signalPowerFromSectors,
                                                       const SectorsControler& sectors,
                                                       int bandIdx):
    m_interferCalc(signalPowerFromSectors, sectors, bandIdx),
    interLvl(0)
{
}

double PixelWorkerForInterference::calculate(InterferenceLvl& intLvl, PixelXY pixel)
{
    double interLvl = m_interferCalc.calculateInterference();
    std::pair<PixelXY,double> pair = std::make_pair(pixel, interLvl);

    if(!std::isinf(interLvl))
    {
        std::unique_lock<std::mutex> lock(mutex);
        intLvl.push_back(pair);
    }
    return interLvl;
}
