#include "InterferenceCalculator.h"
#include "Core/SectorsControler.h"
#include "Common/FrequencyBands.h"
#include <numeric>
#include <algorithm>

InterferenceCalculator::InterferenceCalculator(const std::vector<std::pair<int, double>>& signalFromSectors,
                                               const SectorsControler& sectors,
                                               int bandIdx):
    m_signalFromSectors(signalFromSectors),
    m_sectors(sectors),
    m_currentBandIdx(bandIdx)
{

}

double InterferenceCalculator::calculateInterference()
{
    double interferenceLvl = 0;
    for(auto signalPair : m_signalFromSectors)
    {
        if(signalPair.first == m_currentBandIdx)
        {
            double signalInWat = dBmToW(signalPair.second);
            interferenceLvl = interferenceLvl + signalInWat;
        }
    }
    return WatTodB(interferenceLvl);
}

double InterferenceCalculator::dBmToW(double dBm)
{
    return std::pow(10, dBm/10)/1000;
}

double InterferenceCalculator::WatTodB(double wat)
{
    return std::log10(wat)*10;
}
