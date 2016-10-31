#ifndef PIXELWORKER_H
#define PIXELWORKER_H
#include "Core/PixelXY.h"
#include "AntennaLoss/AntennaLossCalculation.h"
#include "ThreadPool.h"

typedef std::vector<float>& RsrpValueForSectorRef;

class PixelWorker
{
public:
    PixelWorker(std::vector<float> & p_RSRP, RsrpValueForSectorRef p_rsrpSectors, PixelXY p_pixel,
                std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                SectorsControler & p_sectors);

    void executeCalculationForPixel();

private:
    void calculateAntennaLossForOnePixel();

    AntennaLossForSectors antennaLossFromSectorsPerOnePixel;
    std::vector<float> pathLossFromSectorsPerOnePixel; //zmien na sharedPtr

    std::vector<float> & RSRP;
    RsrpValueForSectorRef rsrpSectors;
    PixelXY pixel;
    AntennaLossCalculation antennaCalculation;
};

#endif // PIXELWORKER_H
