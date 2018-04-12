#pragma once
#include <thread>
#include "DataProvider.h"
#include "Interference/InterferenceCalculator.h"

class PixelXY;

class PixelWorkerForInterference
{
public:
    PixelWorkerForInterference(const std::vector<PrbBandAndSignalStrengeMapping>& signalPowerFromSectors,
                               const SectorsControler& sectors,
                               int bandIdx);

    double calculate(InterferenceLvl& intLvl, PixelXY pixel);
private:    
    InterferenceCalculator m_interferCalc;
    double interLvl;
    static std::mutex mutex;
};
