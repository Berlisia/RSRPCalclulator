#pragma once
#include <vector>
#include "PixelWorker.h"

class SectorsControler;
class InterferenceCalculator
{
public:
    InterferenceCalculator(const std::vector<PrbBandAndSignalStrengeMapping>& signalFromSectors,
                           const SectorsControler& sectors,
                           int bandIdx);

    double calculateInterference();
private:
    const std::vector<PrbBandAndSignalStrengeMapping>& m_signalFromSectors; //Band Idx, SignalLvl
    const SectorsControler& m_sectors;
    const int m_currentBandIdx;
};
