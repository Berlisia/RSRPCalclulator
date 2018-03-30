#pragma once
#include <vector>

class SectorsControler;
class InterferenceCalculator
{
public:
    InterferenceCalculator(const std::vector<std::pair<int, double> >& signalFromSectors,
                           const SectorsControler& sectors,
                           int bandIdx);

    double calculateInterference();
private:
    double dBmToW(double dBm);
    double WatTodB(double wat);

    const std::vector<std::pair<int, double> >& m_signalFromSectors; //Band Idx, SignalLvl
    const SectorsControler& m_sectors;
    const int m_currentBandIdx;
};
