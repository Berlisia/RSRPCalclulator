#ifndef WORKER_H
#define WORKER_H
#include "PixelWorker.h"
#include "Core/AreaCalculation.h"
#include "Core/Receiver.h"
#include "DataProvider.h"
#include <QObject>

class PixelWorkerForInterference;
class PixelWorkerForSNIR;

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
    void calculateRsrpForSectors();
    void executeCalculationForPixel(PixelXY pixel);
    bool isBaseStation(PixelXY pixel);
    void deleteNanValue();
    void saveInFile(const std::vector<std::pair<PixelXY, double> >& vector, std::string name);
    const Receiver& setupReciver(const PixelXY& pixel);
    const PixelWorker& calculateSignal(const Receiver& receiver);
    const PixelWorkerForInterference& calculateInterference(const PixelXY& pixel, const PixelWorker& pixelWorker);
    const PixelWorkerForSNIR& calculateSnir(const PixelXY& pixel, const PixelWorker& pixelWorker, const PixelWorkerForInterference& pixelWorkerInt);

    std::unique_ptr<ThreadPool> pool;
    DataProvider & data;
    std::shared_ptr<SectorsControler> sectors;
    std::unique_ptr<AreaCalculation> areaCalculation;

    std::shared_ptr<IMapDataProvider> mapDataProvider;
    std::vector<double> rsrpForSectors;
    RSRPForPixel RSRP;

    std::mutex mut;

};

#endif // WORKER_H
