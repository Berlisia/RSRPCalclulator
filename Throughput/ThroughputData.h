#pragma once
#include <vector>
class Sector;

class ThroughputData
{
public:
    ThroughputData(const Sector& sector);
    void addSnir(double snir);
    double getSectorBandwith() const;
    double calculateAreaCoveragePercentage(double snirTreshold);
    void storeThroughputForSector(double thr);
    double getThroughput() const;
    int getSectorEcgi() const;

private:
    const Sector& sector;
    std::vector<double> snirFromPixels;
    double throughput;
};
