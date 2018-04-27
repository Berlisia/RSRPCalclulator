#include "PixelWorkerForModulation.h"
#include "Core/PixelXY.h"
#include "Common/ModulationSchemes.h"
#include "PixelWorkerForSNIR.h"

std::mutex PixelWorkerForModulation::mutex;


int PixelWorkerForModulation::calculate(PixelXY pixel, double snir, ModulationScheme& modulationVec)
{
    double properCqi = chooseProperCQI(snir);
    auto pair = std::pair<PixelXY, double>(pixel, properCqi);
    if(properCqi != 0)
    {
        std::unique_lock<std::mutex> lock(mutex);
        modulationVec.push_back(pair);
    }
    return properCqi;
}

int PixelWorkerForModulation::chooseProperCQI(double snirValue)
{
    for(std::size_t cqi = 0; cqi < modulationAndSnrMappingTable.size(); cqi++)
    {
        if(snirValue > modulationAndSnrMappingTable[cqi].minSnr and
           snirValue < modulationAndSnrMappingTable[cqi].maxSnr)
        {
            return cqi;
        }
    }
    return 0;
}
