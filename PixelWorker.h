#ifndef PIXELWORKER_H
#define PIXELWORKER_H
#include "Core/PixelXY.h"
#include "AntennaLoss/AntennaLossCalculation.h"
#include "Pathloss/IPathlossCalculation.h"
#include "Core/Receiver.h"
#include "DataProvider.h"
#include "ThreadPool.h"

typedef std::vector<double> & RsrpValueForSectorRef;

class PixelWorker
{
public:
    PixelWorker(RSRPForPixel& p_RSRP, RsrpValueForSectorRef p_rsrpSectors,
                std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                SectorsControler& p_sectors,
                Receiver& p_receiver,
                double p_minValueRSRP);

    void executeCalculation();
    std::vector<std::pair<int,double>>& getResultFromAllSectors();
    int getCurrentBand();
    double getCurrentSignalPower();

private:
    void storeMaxFromRsrpMap();
    void calculateAntennaLossForOnePixel();
    void calculatePathlossForOnePixel();

    AntennaLossForSectors antennaLossFromSectorsPerOnePixel;
    std::vector<double> pathLossFromSectorsPerOnePixel;

    RSRPForPixel& RSRP;
    RsrpValueForSectorRef rsrpSectors;
    const SectorsControler& sectorsControler;
    Receiver& receiver;
    double minValueRSRP;
    AntennaLossCalculation antennaCalculation;
    std::unique_ptr<IPathlossCalculation> pathlossCalculation;

    std::vector<std::pair<int,double>> rsrpFromSectors;
    int currentBand;
    double currentSignalPower;

    static std::mutex mutex;
};

#endif // PIXELWORKER_H
