#include "ThroughputData.h"
#include "Core/Sector.h"

ThroughputData::ThroughputData(const Sector& sector):
    sector(sector), throughput(0)
{
}

void ThroughputData::addSnir(double snir)
{
    snirFromPixels.push_back(snir);
}

double ThroughputData::getSectorBandwith() const
{
    return sector.getBandwith();
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

double ThroughputData::getThroughput() const
{
    return throughput;
}

int ThroughputData::getSectorEcgi() const
{
    return sector.getEcgi();
}
