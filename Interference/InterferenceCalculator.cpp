#include "InterferenceCalculator.h"
#include "Core/SectorsControler.h"
#include "Common/FrequencyBands.h"
#include "Common/Units.h"
#include <numeric>
#include <algorithm>
#include <cmath>

const double numberOfSubcarriersInRB = 12.0;
const double subcarrierActivityFactor = 0.833;

InterferenceCalculator::InterferenceCalculator(const std::vector<PrbBandAndSignalStrengeMapping>& signalFromSectors,
                                               const std::pair<int, double>& servingCellRsrp,
                                               int bandIdx):
    m_signalFromSectors(signalFromSectors),
    m_servingCellRsrp(servingCellRsrp),
    m_currentBandIdx(bandIdx)
{

}

double InterferenceCalculator::calculateInterference()
{
    return calculateSumOfInterferenceFromOtherSectrosForTotalSubcarriers()
            + calculateServingCellSignalForTotalSubcarriers();
}

double InterferenceCalculator::calculateServingCellSignalForTotalSubcarriers()
{
    int numberOfSubcarriers = m_servingCellRsrp.first * numberOfSubcarriersInRB * subcarrierActivityFactor;
    double seringCellRsrpInWat = dBmToW(m_servingCellRsrp.second) * numberOfSubcarriers;
    return WatTodB(seringCellRsrpInWat);
}

double InterferenceCalculator::calculateSumOfInterferenceFromOtherSectrosForTotalSubcarriers()
{
    double interferenceLvl = 0;
    for(auto signalMapping : m_signalFromSectors)
    {
        if(signalMapping.bandIndex == m_currentBandIdx)
        {
            int numberOfSubcarriers = signalMapping.prbNumber * numberOfSubcarriersInRB * subcarrierActivityFactor;
            interferenceLvl = interferenceLvl + dBmToW(signalMapping.signalStrenge)*numberOfSubcarriers;//[W]
        }
    }
    return WatTodB(interferenceLvl);
}
