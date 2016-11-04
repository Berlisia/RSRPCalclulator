#ifndef WORKER_H
#define WORKER_H
#include "PixelWorker.h"
#include "Core/AreaCalculation.h"

class Worker
{
public:
    Worker();

    void doCalculation();
    void listInCoutRSPR();

private:
    void fakeInit(); //TODO whit QT UI
    //klasa InitObject -> zasięg do nazw plików (vector<Antenna>)
    void calculateRsrpForSectors();
    void executeCalculationForPixel(PixelXY pixel);

    std::unique_ptr<ThreadPool> pool;
    std::shared_ptr<SectorsControler> sectors;
    std::unique_ptr<AreaCalculation> areaCalculation;

    std::shared_ptr<IMapDataProvider> dataProvider;
    std::shared_ptr<IAntennaLossFileProvider> antennaProvider; //-> rozszerzyć do kilku anten

    std::vector<float> rsrpForSectors;

    RSRPForPixel RSRP;

    std::mutex mut;

};

#endif // WORKER_H
