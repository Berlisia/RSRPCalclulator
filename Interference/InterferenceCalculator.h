#pragma once
#include <vector>

class InterferenceCalculator
{
public:
    InterferenceCalculator(const std::vector<float>& signalFromSectors);

    float calculateInterference();
private:
    const std::vector<float>& m_signalFromSectors;
};
