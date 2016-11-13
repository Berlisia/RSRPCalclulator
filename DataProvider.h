#ifndef DATASAVER_H
#define DATASAVER_H
#include "Core/BaseStation.h"
#include "Core/SectorsControler.h"
#include "Core/Receiver.h"
#include <memory>

typedef std::vector<std::shared_ptr<BaseStation>> BaseStations;
typedef std::shared_ptr<SectorsControler> SectorsControlerPtr;

class DataProvider
{   
    //Q_OBJECT

public:
    DataProvider()
    {
        sectorControler = std::make_shared<SectorsControler>();
    }

    BaseStations baseStations;
    SectorsControlerPtr sectorControler;
    Receiver receiver;

    std::vector<std::pair<PixelXY,float>> rsrp;

    void addBaseStation(std::shared_ptr<BaseStation> base) {
        baseStations.push_back(base);
    }

    void addSector(Antenna & antenna, std::shared_ptr<BaseStation> base) {
        Sector sector(antenna, base);
        sectorControler->addSector(sector);
    }

    void getRsrp(std::vector<std::pair<PixelXY,float>> & p_rsrp){
        rsrp = std::move(p_rsrp);
    }
};

#endif // DATASAVER_H
