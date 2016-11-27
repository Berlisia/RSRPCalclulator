#ifndef WORKER_H
#define WORKER_H
#include "PixelWorker.h"
#include "Core/AreaCalculation.h"
#include "Core/Receiver.h"
#include "DataProvider.h"
#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(DataProvider & p_data);

    void listInCoutRSPR();
    int getQueueSize() const;
    std::shared_ptr<IMapDataProvider> getMapDataProvider() const;

signals:
    void done();
    void poolStarted();

public slots:
    void doCalculation();

private:
    void fakeInit(); //TODO whit QT UI
    //klasa InitObject -> zasięg do nazw plików (vector<Antenna>)
    void calculateRsrpForSectors();
    void executeCalculationForPixel(PixelXY pixel);
    bool isBaseStation(PixelXY pixel);
    void deleteNanValue();

    std::unique_ptr<ThreadPool> pool;
    DataProvider & data;
    std::shared_ptr<SectorsControler> sectors;
    std::unique_ptr<AreaCalculation> areaCalculation;

    std::shared_ptr<IMapDataProvider> mapDataProvider;
    std::shared_ptr<IAntennaLossFileProvider> antennaProvider; //-> rozszerzyć do kilku anten

    std::vector<float> rsrpForSectors;

    RSRPForPixel RSRP;

    std::mutex mut;

};

#endif // WORKER_H
