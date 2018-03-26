#include "PixelWorkerForInterference.h"
#include "Core/PixelXY.h"

std::mutex PixelWorkerForInterference::mutex;

PixelWorkerForInterference::PixelWorkerForInterference(const std::vector<float>& signalPowerFromSectors):
    m_interferCalc(signalPowerFromSectors)
{

}

void PixelWorkerForInterference::calculate(InterferenceLvl& intLvl, PixelXY pixel)
{
    float interLvl = m_interferCalc.calculateInterference();
    std::pair<PixelXY,float> pair = std::make_pair(pixel, interLvl);
    std::unique_lock<std::mutex> lock(mutex);
    intLvl.push_back(pair);
}
