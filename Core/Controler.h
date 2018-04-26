#pragma once
#include "DataProvider.h"
#include "MapProvider/MapDataProvider.h"
#include "ThreadPool.h"
#include "Worker.h"
#include "mainwindow.h"

#include <QObject>
#include <QThread>

class Controler : public QObject
{
    Q_OBJECT
public:
    Controler(const MainWindow& p_mw,
              DataProvider& p_dataProvider,
              std::shared_ptr<IMapDataProvider> p_mapDataProvider);

    DataProvider& data;
    std::shared_ptr<IMapDataProvider> mapDataProvider;
    std::shared_ptr<ThreadPool> pool;
    Worker worker;
    const MainWindow& mw;
};
