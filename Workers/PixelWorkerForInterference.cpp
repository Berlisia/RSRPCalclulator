#include "PixelWorkerForInterference.h"
#include "Core/PixelXY.h"
#include <algorithm>
#include <QDebug>
std::mutex PixelWorkerForInterference::mutex;

PixelWorkerForInterference::PixelWorkerForInterference(const std::vector<std::pair<int, double> >& signalPowerFromSectors,
                                                       const SectorsControler& sectors,
                                                       int bandIdx):
    m_interferCalc(signalPowerFromSectors, sectors, bandIdx),
    interLvl(0)
{
}

void PixelWorkerForInterference::calculate(InterferenceLvl& intLvl, PixelXY pixel)
{
    interLvl = m_interferCalc.calculateInterference();
    std::pair<PixelXY,double> pair = std::make_pair(pixel, interLvl);

    if(!std::isinf(interLvl))
    {
        std::unique_lock<std::mutex> lock(mutex);
        intLvl.push_back(pair);
    }
}

double PixelWorkerForInterference::getInterferenceLvl()
{
    return interLvl;
}
