#include "ThroughputData.h"

ThroughputData::ThroughputData(const Sector& sector):
    sector(sector), averageSNIR(0)
{
}

void ThroughputData::addSnir(double snir)
{
    snirFromPixels.push_back(snir);
}
