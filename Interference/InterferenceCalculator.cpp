#include "InterferenceCalculator.h"
#include "Core/SectorsControler.h"
#include "Common/FrequencyBands.h"
#include "Common/Units.h"
#include <numeric>
#include <algorithm>

InterferenceCalculator::InterferenceCalculator(const std::vector<PrbBandAndSignalStrengeMapping>& signalFromSectors,
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
    for(auto signalMapping : m_signalFromSectors)
    {
        if(signalMapping.bandIndex == m_currentBandIdx)
        {
            double numberOfSubcarriers = signalMapping.prbNumber * 12;
            interferenceLvl = interferenceLvl + dBmToW(signalMapping.signalStrenge)*numberOfSubcarriers;//[W]
        }
    }
    return WatTodB(interferenceLvl);
}
