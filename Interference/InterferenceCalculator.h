#pragma once
#include <vector>

class SectorsControler;
class InterferenceCalculator
{
public:
    InterferenceCalculator(const std::vector<float>& signalFromSectors,
                           const SectorsControler& sectors);

    float calculateInterference();
private:
    std::iterator findMax();

    const std::vector<float>& m_signalFromSectors;
    const SectorsControler& m_sectors;
};
