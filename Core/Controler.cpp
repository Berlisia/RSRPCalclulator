#include "Controler.h"

Controler::Controler(const MainWindow& p_mw,
                     DataProvider& p_dataProvider,
                     std::shared_ptr<IMapDataProvider> p_mapDataProvider)
    : data(p_dataProvider),
      mapDataProvider(std::move(p_mapDataProvider)),
      pool(std::make_shared<ThreadPool>(std::thread::hardware_concurrency())),
      worker(pool, data, mapDataProvider),
      mw(p_mw)
{
    connect(&mw, &MainWindow::calculationButtonPressed, &worker, &Worker::doCalculation);
    connect(&worker, &Worker::done, &mw, &MainWindow::drawDataMap);
    connect(pool.get(), &ThreadPool::broadcastDataSize, &mw, &MainWindow::setProgressBarRange);
    connect(pool.get(), &ThreadPool::brodcastCurrentPogress, &mw, &MainWindow::updateProgressBar);
}
