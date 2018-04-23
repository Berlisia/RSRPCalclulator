#include <iostream>
#include <QApplication>
#include "Core/Controler.h"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DataProvider data;
    std::shared_ptr<IMapDataProvider> mapDataProvider = std::make_shared<MapDataProvider>();
    MainWindow mw(data, mapDataProvider);

    Controler controler(mw, data, mapDataProvider);
    mw.show();

    return app.exec();
}
