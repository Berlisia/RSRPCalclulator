#include "InterferenceCalculator.h"
#include <numeric>

InterferenceCalculator::InterferenceCalculator(const std::vector<float>& signalFromSectors):
    m_signalFromSectors(signalFromSectors)
{

}

float InterferenceCalculator::calculateInterference()
{
    float interferenceLvl = std::accumulate(m_signalFromSectors.begin(), m_signalFromSectors.end(), 0);
    return interferenceLvl;
}
