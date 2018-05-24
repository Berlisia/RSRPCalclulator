#include "ThroughputData.h"

ThroughputData::ThroughputData(const Sector& sector):
    sector(sector), throughput(0)
{
}

void ThroughputData::addSnir(double snir)
{
    snirFromPixels.push_back(snir);
}

const Sector &ThroughputData::getSectorData()
{
    return sector;
}

double ThroughputData::calculateAreaCoveragePercentage(double snirTreshold)
{
    double sumUpThres = 0;
    for(auto snir: snirFromPixels)
    {
        if(snir > snirTreshold)
        {
            sumUpThres++;
        }
    }
    return sumUpThres/snirFromPixels.size();
}

void ThroughputData::storeThroughputForSector(double thr)
{
    throughput = thr;
}
