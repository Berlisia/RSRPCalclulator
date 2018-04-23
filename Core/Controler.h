#pragma once
#include "mainwindow.h"
#include "MapProvider/MapDataProvider.h"
#include "Worker.h"
#include "DataProvider.h"

#include <QThread>
#include <QObject>

class Controler : public QObject
{
    Q_OBJECT
public:
    Controler(const MainWindow& p_mw, DataProvider& p_dataProvider, std::shared_ptr<IMapDataProvider> p_mapDataProvider);

    QThread thread;
    DataProvider& data;
    std::shared_ptr<IMapDataProvider> mapDataProvider;
    Worker worker;
    const MainWindow& mw;

};
