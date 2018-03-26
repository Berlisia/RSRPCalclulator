#include "InterferenceCalculator.h"
#include "Core/SectorsControler.h"
#include "Common/FrequencyBands.h"
#include <numeric>
#include <algorithm>

InterferenceCalculator::InterferenceCalculator(const std::vector<float>& signalFromSectors,
                                               const SectorsControler& sectors):
    m_signalFromSectors(signalFromSectors),
    m_sectors(sectors)
{

}

float InterferenceCalculator::calculateInterference()
{
    auto maxSignalPower = findMax();
    int possiton = maxSignalPower - m_signalFromSectors.begin();
    //znajdz jaka to cellka / band
    //dodaj do sectora Bandy a nie freq
    //suma tyko na tym samym Bandzie
    float interferenceLvl = std::accumulate(m_signalFromSectors.begin(), m_signalFromSectors.end(), 0);
    return interferenceLvl;
}

std::iterator InterferenceCalculator::findMax()
{
    return std::max_element(std::begin(m_signalFromSectors), std::end(m_signalFromSectors));
}
