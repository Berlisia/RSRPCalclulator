#include "PixelWorker.h"

PixelWorker::PixelWorker(std::vector<float> &p_RSRP, RsrpValueForSectorRef p_rsrpSectors, PixelXY p_pixel,
                         std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                         std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                         SectorsControler &p_sectors) :
    RSRP(p_RSRP), rsrpSectors(p_rsrpSectors), pixel(p_pixel),
    antennaCalculation(AntennaLossCalculation(p_mapDataProvider, p_antennaLossDataProvider, p_sectors))
{
}

void PixelWorker::executeCalculationForPixel()
{
    antennaLossFromSectorsPerOnePixel = antennaCalculation.calculate();
    for (int i = 0; i < antennaLossFromSectorsPerOnePixel->size(); i++)
    {
        RSRP.push_back(rsrpSectors[i] - (*antennaLossFromSectorsPerOnePixel)[i]);
    }

    //TODO
//    float maxValue = rsrpCalculator->findMaxRsrpFromSectors(endedRSRP);
//    RSRP.push_back(std::pair<PixelXY,float>(receiver.getPossition(), maxValue));

//    if(max < maxValue) max = maxValue;
//    if(min > maxValue) min = maxValue;
}
