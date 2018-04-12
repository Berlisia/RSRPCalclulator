#ifndef PIXELWORKER_H
#define PIXELWORKER_H
#include "Core/PixelXY.h"
#include "AntennaLoss/AntennaLossCalculation.h"
#include "Pathloss/IPathlossCalculation.h"
#include "Core/Receiver.h"
#include "DataProvider.h"
#include "ThreadPool.h"

typedef std::vector<std::pair<int,double>>& RsrpValueForSectorRef;

struct PrbBandAndSignalStrengeMapping
{
    int prbNumber;
    int bandIndex;
    double signalStrenge;
};

class PixelWorker
{
public:
    PixelWorker(RSRPForPixel& p_RSRP, RsrpValueForSectorRef p_rsrpSectors,
                std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                SectorsControler& p_sectors,
                const Receiver& p_receiver,
                double p_minValueRSRP);
    PixelWorker(PixelWorker&&) = default;
    PixelWorker(const PixelWorker&) = delete;

    void executeCalculation();
    const std::vector<PrbBandAndSignalStrengeMapping> &getResultFromAllSectors() const;
    int getCurrentBand() const;
    std::pair<int,double> getCurrentSignalPower() const;

private:
    void storeMaxFromRsrpMap();
    void calculateAntennaLossForOnePixel();
    void calculatePathlossForOnePixel();

    AntennaLossForSectors antennaLossFromSectorsPerOnePixel;
    std::vector<double> pathLossFromSectorsPerOnePixel;

    RSRPForPixel& RSRP;
    RsrpValueForSectorRef rsrpSectors;
    const SectorsControler& sectorsControler;
    const Receiver& receiver;
    double minValueRSRP;
    AntennaLossCalculation antennaCalculation;
    std::unique_ptr<IPathlossCalculation> pathlossCalculation;

    std::vector<PrbBandAndSignalStrengeMapping> rsrpFromSectors;
    int currentBand;
    std::pair<int,double> currentSignalPower;

    static std::mutex mutex;
};

#endif // PIXELWORKER_H
