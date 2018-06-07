#include "DataProvider.h"
#include "MapProvider/GeographicalCoordinatesConverter.h"
#include <QDebug>

//std::string h = "D:/Polibuda/Mgr/lato2017_2018/PracaMgr/RSRPCalclulator/742266V02_pozioma.csv";
//std::string v = "D:/Polibuda/Mgr/lato2017_2018/PracaMgr/RSRPCalclulator/742266V02_pionowa.csv";
std::string h = "/home/eberlick/PracaMgr/Repo/RSRPCalclulator/742266V02_pozioma.csv";
std::string v = "/home/eberlick/PracaMgr/Repo/RSRPCalclulator/742266V02_pionowa.csv";
std::string v_40 = "/home/eberlick/PracaMgr/Repo/RSRPCalclulator/charakterystyka_anteny_40_vertical.csv";
std::string h_40 = "/home/eberlick/PracaMgr/Repo/RSRPCalclulator/charakterystyka_anteny_40_horizontal.csv";

DataProvider::DataProvider() : minValueOfRSRP(-120)
{
    sectorControler = std::make_shared<SectorsControler>();
    receiver.setHeight(1);
    receiver.setGain(0);
    receiver.setOtherLosses(0);

    dataFor60Klaster();
}

void DataProvider::addBaseStation(std::shared_ptr<BaseStation> base)
{
    baseStations.push_back(std::move(base));
}

void DataProvider::addSector(Antenna &antenna, std::shared_ptr<BaseStation> base)
{
    Sector sector(antenna, std::move(base));
    sectorControler->addSector(sector);
}

void DataProvider::getRsrp(std::vector<std::pair<PixelXY, double> > p_rsrp)
{
    rsrp.vector = std::move(p_rsrp);
}

void DataProvider::updateInputValueForSector(int ecgi, QString p_filed, QString p_value)
{
    sectorControler->modify(ecgi, std::move(p_filed), std::move(p_value));
}

void DataProvider::updateInputValueForBaseStation(QString p_eNbId, QString p_field, QString p_value)
{
    qDebug() << "enb: " << p_eNbId;
    qDebug() << "pole: " << p_field;
    qDebug() << "wartosc: " << p_value;
}

void DataProvider::clearCalculationData()
{
    rsrp.vector.clear();
    rsrq.clear();
    snir.clear();
    modulation.clear();
    interferenceLvl.clear();
}

void DataProvider::dataFor120Klaster()
{
    DodawaczkaSectorow adder(baseStations, sectorControler);
    adder.addBS(50.919689, 16.430065, 23, "JaworzynaSląska"); //0
    adder.addBS(51.036416, 16.427318, 23, "Udanin"); //1
    adder.addBS(50.978954, 16.248791, 23, "Dobromierz"); //2
    adder.addBS(50.855580, 16.254284, 23, "StareBogaczowice"); //3
    adder.addBS(50.783136, 16.426632, 23, "BystrzycaGórna"); //4
    adder.addBS(50.852979, 16.599666, 23, "Marcinowice"); //5
    adder.addBS(50.976792, 16.590740, 23, "Mietków"); //6

    //JaworzynaSląska
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 330, Mimo::TwoAntenna, Environment::SuburbanEvironments, 1, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 90, Mimo::TwoAntenna, Environment::SuburbanEvironments, 2, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 210, Mimo::TwoAntenna, Environment::SuburbanEvironments, 3, Model::Cost231Hata);

    //Udanin
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 4, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 270, Mimo::TwoAntenna, Environment::SuburbanEvironments, 5, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 150, Mimo::TwoAntenna, Environment::SuburbanEvironments, 6, Model::Cost231Hata);

    //Dobromierz
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 330, Mimo::TwoAntenna, Environment::SuburbanEvironments, 7, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 90, Mimo::TwoAntenna, Environment::SuburbanEvironments, 8, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 210, Mimo::TwoAntenna, Environment::SuburbanEvironments, 9, Model::Cost231Hata);

    //StareBogaczowice
    adder.addSector(45, 15, 5, 1, h_40, v_40, baseStations[3], 15, 30, Mimo::TwoAntenna, Environment::SuburbanEvironments, 10, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[3], 15, 150, Mimo::TwoAntenna, Environment::SuburbanEvironments, 11, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[3], 15, 270, Mimo::TwoAntenna, Environment::SuburbanEvironments, 12, Model::Cost231Hata);

    //BystrzycaGórna
    adder.addSector(45, 15, 4, 1, h_40, v_40, baseStations[4], 15, 30, Mimo::TwoAntenna, Environment::SuburbanEvironments, 13, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[4], 15, 150, Mimo::TwoAntenna, Environment::SuburbanEvironments, 14, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[4], 15, 270, Mimo::TwoAntenna, Environment::SuburbanEvironments, 15, Model::Cost231Hata);

    //Marcinowice
    adder.addSector(45, 15, 4, 1, h_40, v_40, baseStations[5], 15, 30, Mimo::TwoAntenna, Environment::SuburbanEvironments, 16, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[5], 15, 150, Mimo::TwoAntenna, Environment::SuburbanEvironments, 17, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[5], 15, 270, Mimo::TwoAntenna, Environment::SuburbanEvironments, 18, Model::Cost231Hata);

    //Mietków
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 30, Mimo::TwoAntenna, Environment::SuburbanEvironments, 19, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 150, Mimo::TwoAntenna, Environment::SuburbanEvironments, 20, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 270, Mimo::TwoAntenna, Environment::SuburbanEvironments, 21, Model::Cost231Hata);
}

void DataProvider::dataFor60Klaster()
{
    DodawaczkaSectorow adder(baseStations, sectorControler);
    adder.addBS(50.919689, 16.430065, 23, "JaworzynaSląska"); //0
    adder.addBS(51.036416, 16.427318, 23, "Udanin"); //1
    adder.addBS(50.978954, 16.248791, 23, "Dobromierz"); //2
    adder.addBS(50.855580, 16.254284, 23, "StareBogaczowice"); //3
    adder.addBS(50.783136, 16.426632, 23, "BystrzycaGórna"); //4
    adder.addBS(50.852979, 16.599666, 23, "Marcinowice"); //5
    adder.addBS(50.976792, 16.590740, 23, "Mietków"); //6

    //JaworzynaSląska
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 0, Mimo::TwoAntenna, Environment::SuburbanEvironments, 1, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 2, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 120, Mimo::TwoAntenna, Environment::SuburbanEvironments, 3, Model::Cost231Hata);

    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 180, Mimo::TwoAntenna, Environment::SuburbanEvironments, 4, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 240, Mimo::TwoAntenna, Environment::SuburbanEvironments, 5, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[0], 15, 300, Mimo::TwoAntenna, Environment::SuburbanEvironments,6, Model::Cost231Hata);

    //Udanin
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 0, Mimo::TwoAntenna, Environment::SuburbanEvironments, 7, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 8, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 120, Mimo::TwoAntenna, Environment::SuburbanEvironments, 9, Model::Cost231Hata);

    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 180, Mimo::TwoAntenna, Environment::SuburbanEvironments, 4, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 240, Mimo::TwoAntenna, Environment::SuburbanEvironments, 5, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[1], 15, 300, Mimo::TwoAntenna, Environment::SuburbanEvironments, 6, Model::Cost231Hata);

    //Dobromierz
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 0, Mimo::TwoAntenna, Environment::SuburbanEvironments, 7, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 8, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 120, Mimo::TwoAntenna, Environment::SuburbanEvironments, 9, Model::Cost231Hata);

    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 180, Mimo::TwoAntenna, Environment::SuburbanEvironments, 7, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 240, Mimo::TwoAntenna, Environment::SuburbanEvironments, 8, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[2], 15, 300, Mimo::TwoAntenna, Environment::SuburbanEvironments, 9, Model::Cost231Hata);

    //StareBogaczowice
    adder.addSector(45, 15, 5, 1, h_40, v_40, baseStations[3], 15, 0, Mimo::TwoAntenna, Environment::SuburbanEvironments, 10, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[3], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 11, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[3], 15, 120, Mimo::TwoAntenna, Environment::SuburbanEvironments, 12, Model::Cost231Hata);

    adder.addSector(45, 15, 5, 1, h_40, v_40, baseStations[3], 15, 180, Mimo::TwoAntenna, Environment::SuburbanEvironments, 10, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[3], 15, 240, Mimo::TwoAntenna, Environment::SuburbanEvironments, 11, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[3], 15, 300, Mimo::TwoAntenna, Environment::SuburbanEvironments, 12, Model::Cost231Hata);

    //BystrzycaGórna
    adder.addSector(45, 15, 4, 1, h_40, v_40, baseStations[4], 15, 0, Mimo::TwoAntenna, Environment::SuburbanEvironments, 13, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[4], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 14, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[4], 15, 120, Mimo::TwoAntenna, Environment::SuburbanEvironments, 15, Model::Cost231Hata);

    adder.addSector(45, 15, 4, 1, h_40, v_40, baseStations[4], 15, 180, Mimo::TwoAntenna, Environment::SuburbanEvironments, 13, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[4], 15, 240, Mimo::TwoAntenna, Environment::SuburbanEvironments, 14, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[4], 15, 300, Mimo::TwoAntenna, Environment::SuburbanEvironments, 15, Model::Cost231Hata);

    //Marcinowice
    adder.addSector(45, 15, 4, 1, h_40, v_40, baseStations[5], 15, 0, Mimo::TwoAntenna, Environment::SuburbanEvironments, 16, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[5], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 17, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[5], 15, 120, Mimo::TwoAntenna, Environment::SuburbanEvironments, 18, Model::Cost231Hata);

    adder.addSector(45, 15, 4, 1, h_40, v_40, baseStations[5], 15, 180, Mimo::TwoAntenna, Environment::SuburbanEvironments, 16, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[5], 15, 240, Mimo::TwoAntenna, Environment::SuburbanEvironments, 17, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[5], 15, 300, Mimo::TwoAntenna, Environment::SuburbanEvironments, 18, Model::Cost231Hata);

    //Mietków
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 0, Mimo::TwoAntenna, Environment::SuburbanEvironments, 19, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 60, Mimo::TwoAntenna, Environment::SuburbanEvironments, 20, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 120, Mimo::TwoAntenna, Environment::SuburbanEvironments, 21, Model::Cost231Hata);

    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 180, Mimo::TwoAntenna, Environment::SuburbanEvironments, 19, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 240, Mimo::TwoAntenna, Environment::SuburbanEvironments, 20, Model::Cost231Hata);
    adder.addSector(45, 15, 3, 1, h_40, v_40, baseStations[6], 15, 300, Mimo::TwoAntenna, Environment::SuburbanEvironments, 21, Model::Cost231Hata);
}


void DataProvider::fakeDataForDebuging2()
{
    DodawaczkaSectorow adder(baseStations, sectorControler);
    adder.addBS(51.2611, 16.4689, 23, "bts1");
    adder.addSector(41, 15, 3, 3, h_40, v_40, baseStations[0],
                    10, 180, Mimo::Nan, Environment::SmallAndMediumSizeCities,
                    1, Model::Cost231Hata);
}

void DodawaczkaSectorow::addBS(double x, double y, int height, std::string name)
{
    GeographicalCoordinatesConverter geoConverter;
    std::pair<int,int> pixel = geoConverter.geographicalCoordinatesToPixel(std::pair<double,double>(x,y));
    PixelXY possition(pixel);
    bsVector.push_back(std::make_shared<BaseStation>(possition.getXy(), height, name));
}

void DodawaczkaSectorow::addSector(double power, double gain, int tilt, int bandBw, std::string fileH, std::string fileV,
                                   std::shared_ptr<BaseStation> baseStation,
                                   double bandwidth, int azimuth, Mimo mimo,
                                   Environment env, int ecgi, Model model)
{
    Antenna antenna(power, gain, tilt, bandBw, fileH, fileV);
    std::shared_ptr<IAntennaLossFileProvider> antennaLossFileProvider = std::make_shared<AntennaLossFileProvider>(h,v);
    Sector sector1(antenna, baseStation);
    sector1.setBandwidth(bandwidth);
    sector1.setAzimuth(azimuth);
    sector1.setMimo(mimo);
    sector1.setEnvironment(env);
    sector1.setEcgi(ecgi);
    sector1.setAntennaCharacteristic(antennaLossFileProvider);
    sector1.setModel(model);
    secControl->addSector(sector1);
}
