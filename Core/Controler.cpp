#include "Controler.h"

Controler::Controler(const MainWindow &p_mw, DataProvider &p_dataProvider, std::shared_ptr<IMapDataProvider> p_mapDataProvider):
    data(p_dataProvider),
    mapDataProvider(p_mapDataProvider),
    worker(data, mapDataProvider),
    mw(p_mw)
{
    connect(&mw, &MainWindow::calculationButtonPressed, &worker, &Worker::doCalculation);
    connect(&worker, &Worker::done, &mw, &MainWindow::drawDataMap);
    worker.moveToThread(&thread);
    thread.start();
}
