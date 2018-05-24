#pragma once
#include <vector>
class Sector;

class ThroughputData
{
public:
    ThroughputData(const Sector& sector);
    void addSnir(double snir);
    const Sector& getSectorData();
    double calculateAreaCoveragePercentage(double snirTreshold);
    void storeThroughputForSector(double thr);

private:
    const Sector& sector;
    std::vector<double> snirFromPixels;
    double throughput;
};
