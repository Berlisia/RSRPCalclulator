#ifndef PIXELWORKER_H
#define PIXELWORKER_H
#include "Core/PixelXY.h"
#include "AntennaLoss/AntennaLossCalculation.h"
#include "Pathloss/IPathlossCalculation.h"
#include "Core/Receiver.h"
#include "ThreadPool.h"

typedef std::vector<float>& RsrpValueForSectorRef;
typedef std::vector<std::pair<PixelXY,float>> RSRPForPixel;

class PixelWorker
{
public:
    PixelWorker(RSRPForPixel & p_RSRP, RsrpValueForSectorRef p_rsrpSectors,
                std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                SectorsControler & p_sectors,
                Receiver & p_receiver);

    void executeCalculation();
    float findMaxFrom(const std::vector<float> & vector);

private:
    void calculateAntennaLossForOnePixel();
    void calculatePathlossForOnePixel();

    AntennaLossForSectors antennaLossFromSectorsPerOnePixel;
    std::vector<float> pathLossFromSectorsPerOnePixel; //zmien na sharedPtr

    RSRPForPixel & RSRP;
    RsrpValueForSectorRef rsrpSectors;
    Receiver & receiver;
    AntennaLossCalculation antennaCalculation;
    std::unique_ptr<IPathlossCalculation> pathlossCalculation;

    static std::mutex mutex;
};

#endif // PIXELWORKER_H
