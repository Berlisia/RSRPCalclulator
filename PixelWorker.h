#ifndef PIXELWORKER_H
#define PIXELWORKER_H
#include "Core/PixelXY.h"
#include "AntennaLoss/AntennaLossCalculation.h"
#include "ThreadPool.h"

typedef std::vector<float>& RsrpValueForSectorRef;
typedef std::vector<std::pair<PixelXY,float>> RSRPForPixel;

class PixelWorker
{
public:
    PixelWorker(RSRPForPixel & p_RSRP, RsrpValueForSectorRef p_rsrpSectors, PixelXY p_pixel,
                std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                SectorsControler & p_sectors);

    void executeCalculation();
    float findMaxFrom(const std::vector<float> & vector);

private:
    void calculateAntennaLossForOnePixel();

    AntennaLossForSectors antennaLossFromSectorsPerOnePixel;
    std::vector<float> pathLossFromSectorsPerOnePixel; //zmien na sharedPtr

    RSRPForPixel & RSRP;
    RsrpValueForSectorRef rsrpSectors;
    PixelXY pixel;
    AntennaLossCalculation antennaCalculation;

    static std::mutex mutex;
};

#endif // PIXELWORKER_H
