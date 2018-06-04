#ifndef DATASAVER_H
#define DATASAVER_H
#include "Core/BaseStation.h"
#include "Core/SectorsControler.h"
#include "Core/Receiver.h"
#include "Throughput/ThroughputData.h"
#include <QObject>
#include <memory>
#include <mutex>

typedef std::vector<std::shared_ptr<BaseStation>> BaseStations;
typedef std::shared_ptr<SectorsControler> SectorsControlerPtr;
typedef std::vector<std::pair<int,int>> BoundaryPixelsInArea;
typedef std::vector<std::pair<PixelXY,double>> InterferenceLvl;
typedef std::vector<std::pair<PixelXY,double>> Snir;
typedef std::vector<std::pair<PixelXY,double>> SignalPower;
typedef std::vector<std::pair<PixelXY,double>> ModulationScheme;
typedef std::vector<std::pair<PixelXY,double>> Rsrq;
typedef std::vector<ThroughputData> Throughput;

class RSRPForPixel : public QObject
{
    Q_OBJECT
public:
    SignalPower vector;
signals:
    void rsrpSizeChanged();
};

struct DodawaczkaSectorow
{
    DodawaczkaSectorow(BaseStations& bsVector, SectorsControlerPtr secControl):
        bsVector(bsVector), secControl(secControl)
    {}

    BaseStations& bsVector;
    SectorsControlerPtr secControl;

    void addBS(double x, double y, int height, std::string name);
    void addSector(double power, double gain, int tilt, int bandBw, std::string fileH, std::string fileV,
                   std::shared_ptr<BaseStation> baseStation,
                   double bandwidth, int azimuth, Mimo mimo,
                   Environment env, int ecgi, Model model);
};

class DataProvider
{   
public:
    DataProvider();

    void addBaseStation(std::shared_ptr<BaseStation> base);
    void addSector(Antenna& antenna, std::shared_ptr<BaseStation> base);
    void getRsrp(std::vector<std::pair<PixelXY, double> > p_rsrp);
    void updateInputValueForSector(int ecgi, QString, QString);
    void updateInputValueForBaseStation(QString, QString, QString);
    void clearCalculationData();

    BaseStations baseStations;
    SectorsControlerPtr sectorControler;
    Receiver receiver;
    double minValueOfRSRP;
    BoundaryPixelsInArea areaPixels;

    RSRPForPixel rsrp;
    InterferenceLvl interferenceLvl;
    Rsrq rsrq;
    Snir snir;
    ModulationScheme modulation;
    Throughput throughput;

private:
    void dataFor120Klaster();
    void fakeDataForDebuging2();
};

#endif // DATAProvider_H
