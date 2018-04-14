#pragma once
#include <thread>
#include "DataProvider.h"
#include "Interference/InterferenceCalculator.h"

class PixelXY;

class PixelWorkerForInterference
{
public:
    PixelWorkerForInterference(const std::vector<PrbBandAndSignalStrengeMapping>& signalPowerFromSectors,
                               const std::pair<int,double>& servingCellRsrp,
                               int bandIdx);

    double calculate(InterferenceLvl& intLvl, PixelXY pixel);
private:    
    InterferenceCalculator m_interferCalc;
    static std::mutex mutex;
};
