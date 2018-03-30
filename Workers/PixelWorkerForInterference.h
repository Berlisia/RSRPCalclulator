#pragma once
#include <thread>
#include "DataProvider.h"
#include "Interference/InterferenceCalculator.h"

class PixelXY;

class PixelWorkerForInterference
{
public:
    PixelWorkerForInterference(const std::vector<std::pair<int, double>>& signalPowerFromSectors,
                               const SectorsControler& sectors,
                               int bandIdx);

    void calculate(InterferenceLvl& intLvl, PixelXY pixel);
    double getInterferenceLvl();
private:    
    InterferenceCalculator m_interferCalc;
    double interLvl;
    static std::mutex mutex;
};
