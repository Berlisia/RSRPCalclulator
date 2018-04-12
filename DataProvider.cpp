#include "DataProvider.h"
#include "MapProvider/GeographicalCoordinatesConverter.h"
#include <QDebug>

DataProvider::DataProvider() : minValueOfRSRP(-120)
{
    sectorControler = std::make_shared<SectorsControler>();
    receiver.setHeight(1);
    receiver.setGain(0);
    receiver.setOtherLosses(0);

    fakeDataForDebuging();
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

void DataProvider::getRsrp(std::vector<std::pair<PixelXY, double> > &p_rsrp)
{
    rsrp.vector = std::move(p_rsrp);
}

void DataProvider::updateInputValueForSector(const int ecgi, const QString p_filed, const QString p_value)
{
    sectorControler->modify(ecgi, p_filed, p_value);
}

void DataProvider::updateInputValueForBaseStation(const QString p_eNbId, const QString p_field, const QString p_value)
{
    qDebug() << "enb: " << p_eNbId;
    qDebug() << "pole: " << p_field;
    qDebug() << "wartosc: " << p_value;
}

void DataProvider::fakeDataForDebuging()
{
    double x = 50.9758;
    double y = 16.1613;
    GeographicalCoordinatesConverter geoConverter;
    std::pair<int,int> pixel = geoConverter.geographicalCoordinatesToPixel(std::pair<double,double>(x,y));
    PixelXY possition(pixel);
    baseStations.push_back(std::make_shared<BaseStation>(std::move(possition.getXy()),15,"bts1"));

    std::string h = "D:/Polibuda/Mgr/lato2017_2018/PracaMgr/RSRPCalclulator/742266V02_pozioma.csv";
    std::string v = "D:/Polibuda/Mgr/lato2017_2018/PracaMgr/RSRPCalclulator/742266V02_pionowa.csv";
    Antenna antenna(45, 15, 2,1,h,v);
    Antenna antenna2(30, 15, 2,3,h,v);
    Antenna antenna3(30, 15, 2,7,h,v);
    Antenna antenna4(30, 15, 2,8,h,v);
    Antenna antenna5(30, 15, 2,20,h,v);
    Antenna antenna6(30, 15, 2,38,h,v);
    std::shared_ptr<IAntennaLossFileProvider> antennaLossFileProvider = std::make_shared<AntennaLossFileProvider>(h,v);

    Sector sector1(antenna, baseStations[0]);
    sector1.setBandwidth(5);
    sector1.setAzimuth(45);
    sector1.setMimo(Mimo::Nan);
    sector1.setEnvironment(Environment::RuralAera);
    sector1.setEcgi(1);
    sector1.setAntennaCharacteristic(antennaLossFileProvider);
    sector1.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector1);

    Sector sector2(antenna, baseStations[0]);
    sector2.setBandwidth(5);
    sector2.setAzimuth(90);
    sector2.setMimo(Mimo::Nan);
    sector2.setEnvironment(Environment::RuralAera);
    sector2.setEcgi(2);
    sector2.setAntennaCharacteristic(antennaLossFileProvider);
    sector2.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector2);

    Sector sector3(antenna, baseStations[0]);
    sector3.setBandwidth(5);
    sector3.setAzimuth(180);
    sector3.setMimo(Mimo::Nan);
    sector3.setEnvironment(Environment::RuralAera);
    sector3.setEcgi(3);
    sector3.setAntennaCharacteristic(antennaLossFileProvider);
    sector3.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector3);

    x = 50.9713;
    y = 16.3100;
    pixel = geoConverter.geographicalCoordinatesToPixel(std::pair<double,double>(x,y));
    PixelXY possition2(pixel);
    baseStations.push_back(std::make_shared<BaseStation>(std::move(possition2.getXy()),20,"bts2"));

    Sector sector4(antenna, baseStations[1]);
    sector4.setBandwidth(5);
    sector4.setAzimuth(315);
    sector4.setMimo(Mimo::Nan);
    sector4.setEnvironment(Environment::RuralAera);
    sector4.setEcgi(4);
    sector4.setAntennaCharacteristic(antennaLossFileProvider);
    sector4.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector4);

    Sector sector5(antenna, baseStations[1]);
    sector5.setBandwidth(5);
    sector5.setAzimuth(270);
    sector5.setMimo(Mimo::Nan);
    sector5.setEnvironment(Environment::RuralAera);
    sector5.setEcgi(5);
    sector5.setAntennaCharacteristic(antennaLossFileProvider);
    sector5.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector5);

    Sector sector6(antenna, baseStations[1]);
    sector6.setBandwidth(5);
    sector6.setAzimuth(200);
    sector6.setMimo(Mimo::Nan);
    sector6.setEnvironment(Environment::RuralAera);
    sector6.setEcgi(6);
    sector6.setAntennaCharacteristic(antennaLossFileProvider);
    sector6.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector6);

    x = 50.9112;
    y = 16.2177;
    pixel = geoConverter.geographicalCoordinatesToPixel(std::pair<double,double>(x,y));
    PixelXY possition3(pixel);
    baseStations.push_back(std::make_shared<BaseStation>(std::move(possition3.getXy()),15,"bts3"));

    Sector sector7(antenna, baseStations[2]);
    sector7.setBandwidth(5);
    sector7.setAzimuth(350);
    sector7.setMimo(Mimo::Nan);
    sector7.setEnvironment(Environment::RuralAera);
    sector7.setEcgi(7);
    sector7.setAntennaCharacteristic(antennaLossFileProvider);
    sector7.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector7);

    Sector sector8(antenna, baseStations[2]);
    sector8.setBandwidth(5);
    sector8.setAzimuth(280);
    sector8.setMimo(Mimo::Nan);
    sector8.setEnvironment(Environment::RuralAera);
    sector8.setEcgi(8);
    sector8.setAntennaCharacteristic(antennaLossFileProvider);
    sector8.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector8);

    Sector sector9(antenna, baseStations[2]);
    sector9.setBandwidth(5);
    sector9.setAzimuth(190);
    sector9.setMimo(Mimo::Nan);
    sector9.setEnvironment(Environment::RuralAera);
    sector9.setEcgi(9);
    sector9.setAntennaCharacteristic(antennaLossFileProvider);
    sector9.setModel(Model::Cost231Hata);
    sectorControler->addSector(sector9);
}
