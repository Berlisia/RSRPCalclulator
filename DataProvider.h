#ifndef DATASAVER_H
#define DATASAVER_H
#include "Core/BaseStation.h"
#include "Core/SectorsControler.h"
#include "Core/Receiver.h"
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

class RSRPForPixel : public QObject
{
    Q_OBJECT

public:
    SignalPower vector;
signals:
    void rsrpSizeChanged();
};

class DataProvider
{   
public:
    DataProvider();

    void addBaseStation(std::shared_ptr<BaseStation> base);
    void addSector(Antenna& antenna, std::shared_ptr<BaseStation> base);
    void getRsrp(std::vector<std::pair<PixelXY,double>>& p_rsrp);
    void updateInputValueForSector(const int ecgi, const QString, const QString);
    void updateInputValueForBaseStation(const QString, const QString, const QString);

    BaseStations baseStations;
    SectorsControlerPtr sectorControler;
    Receiver receiver;
    double minValueOfRSRP;
    BoundaryPixelsInArea areaPixels;

    RSRPForPixel rsrp;
    InterferenceLvl interferenceLvl;
    Snir snir;
    ModulationScheme modulation;

private:
    void fakeDataForDebuging();
};

#endif // DATAProvider_H
