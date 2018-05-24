#pragma once
#include <vector>
class Sector;

class ThroughputData
{
public:
    ThroughputData(const Sector& sector);
    void addSnir(double snir);

private:
    const Sector& sector;
    std::vector<double> snirFromPixels;
    double averageSNIR;
};
