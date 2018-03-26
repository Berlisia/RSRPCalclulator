#pragma once
#include <vector>
#include <thread>
#include "DataProvider.h"
#include "Interference/InterferenceCalculator.h"

class PixelXY;

class PixelWorkerForInterference
{
public:
    PixelWorkerForInterference(const std::vector<float>& signalPowerFromSectors);

    void calculate(InterferenceLvl& intLvl, PixelXY pixel);
private:
    InterferenceCalculator m_interferCalc;

    static std::mutex mutex;
};
