#include "DataProvider.h"


DataProvider::DataProvider() : minValueOfRSRP(-120)
{
    sectorControler = std::make_shared<SectorsControler>();
    receiver.setHeight(1);
    receiver.setGain(0);
    receiver.setOtherLosses(0);
}

void DataProvider::addBaseStation(std::shared_ptr<BaseStation> base)
{
    baseStations.push_back(base);
}

void DataProvider::addSector(Antenna &antenna, std::shared_ptr<BaseStation> base)
{
    Sector sector(antenna, base);
    sectorControler->addSector(sector);
}

void DataProvider::getRsrp(std::vector<std::pair<PixelXY, float> > &p_rsrp)
{
    rsrp.vector = std::move(p_rsrp);
}

void DataProvider::updateInputValue(QString p_filed, QString p_value)
{

}
