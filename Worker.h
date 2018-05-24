#ifndef WORKER_H
#define WORKER_H
#include "Core/AreaCalculation.h"
#include "Core/Receiver.h"
#include "DataProvider.h"
#include "PixelWorker.h"
#include <QObject>
#include <QFuture>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(std::shared_ptr<ThreadPool> p_pool,
           DataProvider& p_data,
           std::shared_ptr<IMapDataProvider> p_mapDataProvider);

    void listInCoutRSPR();

signals:
    void done();
    void poolStarted();

public slots:
    void doCalculation();

private:
    void makeQueueOfCalculationTaskAndRun();
    void calculateRsrpForSectors();
    void executeCalculationForPixel(PixelXY pixel);
    bool isBaseStation(PixelXY pixel);
    void deleteNanValue();
    void saveInFile(const std::vector<std::pair<PixelXY, double>>& vector, std::string name);
    Receiver setupReciver(const PixelXY& pixel);
    double calculateInterference(const PixelXY& pixel, const PixelWorker& pixelWorker);
    double calculateSnir(const PixelXY& pixel, double signalLvl);
    void initializeThrouputData();

    std::shared_ptr<ThreadPool> pool;
    QFuture<void> future;
    DataProvider& data;
    std::shared_ptr<IMapDataProvider> mapDataProvider;
    std::shared_ptr<SectorsControler> sectors;
    std::unique_ptr<AreaCalculation> areaCalculation;

    std::vector<std::pair<int, double>> rsrpForSectors;
    RSRPForPixel RSRP;

    static std::mutex mut;
};

#endif // WORKER_H
