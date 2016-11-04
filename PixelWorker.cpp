#include "PixelWorker.h"
#include <algorithm>
#include <iostream>

std::mutex PixelWorker::mutex;

PixelWorker::PixelWorker(RSRPForPixel & p_RSRP,
                         RsrpValueForSectorRef p_rsrpSectors,
                         PixelXY p_pixel,
                         std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                         std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                         SectorsControler & p_sectors) :
    RSRP(p_RSRP), rsrpSectors(p_rsrpSectors), pixel(p_pixel),
    antennaCalculation(AntennaLossCalculation(p_mapDataProvider, p_antennaLossDataProvider, p_sectors))
{
}

void PixelWorker::executeCalculation()
{
    std::vector<float> rsrpFromSectors;
    antennaCalculation.setReciver(pixel);
    antennaLossFromSectorsPerOnePixel = antennaCalculation.calculate();
    for (unsigned int i = 0; i < antennaLossFromSectorsPerOnePixel->size(); i++)
    {
        rsrpFromSectors.push_back(rsrpSectors[i] - (*antennaLossFromSectorsPerOnePixel)[i]);
    }
    float maxValue = findMaxFrom(rsrpFromSectors);
    std::unique_lock<std::mutex> lock(mutex);
    RSRP.push_back(std::pair<PixelXY,float>(pixel, maxValue));
}

float PixelWorker::findMaxFrom(const std::vector<float> &vector)
{
    auto biggest = std::max_element(std::begin(vector), std::end(vector));
    return *biggest;
}
