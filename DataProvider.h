#ifndef DATASAVER_H
#define DATASAVER_H
#include "Core/BaseStation.h"
#include "Core/SectorsControler.h"
#include "Core/Receiver.h"
#include <QObject>
#include <memory>

typedef std::vector<std::shared_ptr<BaseStation>> BaseStations;
typedef std::shared_ptr<SectorsControler> SectorsControlerPtr;

class RSRPForPixel : public QObject
{
    Q_OBJECT

public:
    std::vector<std::pair<PixelXY,float>> vector;
signals:
    void rsrpSizeChanged();
};

class DataProvider
{   
public:
    DataProvider() : minValueOfRSRP(-140)
    {
        sectorControler = std::make_shared<SectorsControler>();
        receiver.setHeight(1);
    }

    BaseStations baseStations;
    SectorsControlerPtr sectorControler;
    Receiver receiver;
    double minValueOfRSRP;

    RSRPForPixel rsrp;

    void addBaseStation(std::shared_ptr<BaseStation> base) {
        baseStations.push_back(base);
    }

    void addSector(Antenna & antenna, std::shared_ptr<BaseStation> base) {
        Sector sector(antenna, base);
        sectorControler->addSector(sector);
    }

    void getRsrp(std::vector<std::pair<PixelXY,float>> & p_rsrp){
        rsrp.vector = std::move(p_rsrp);
    }
};

#endif // DATAProvider_H
