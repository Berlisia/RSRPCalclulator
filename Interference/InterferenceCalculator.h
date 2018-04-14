#pragma once
#include <vector>
#include "PixelWorker.h"

class SectorsControler;
class InterferenceCalculator
{
public:
    InterferenceCalculator(const std::vector<PrbBandAndSignalStrengeMapping>& signalFromSectors,
                           const std::pair<int,double>& servingCellRsrp,
                           int bandIdx);

    double calculateInterference();
private:
    double calculateServingCellSignalForTotalSubcarriers();
    double calculateSumOfInterferenceFromOtherSectrosForTotalSubcarriers();

    const std::vector<PrbBandAndSignalStrengeMapping>& m_signalFromSectors; //Band Idx, SignalLvl
    const std::pair<int,double>& m_servingCellRsrp;
    const int m_currentBandIdx;
};
