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
    DataProvider();

    void addBaseStation(std::shared_ptr<BaseStation> base);
    void addSector(Antenna& antenna, std::shared_ptr<BaseStation> base);
    void getRsrp(std::vector<std::pair<PixelXY,float>>& p_rsrp);
    void updateInputValueForSector(int ecgi, QString, QString);
    void updateInputValueForBaseStation(QString, QString, QString);

    BaseStations baseStations;
    SectorsControlerPtr sectorControler;
    Receiver receiver;
    double minValueOfRSRP;
    BoundaryPixelsInArea areaPixels;

    RSRPForPixel rsrp;
};

#endif // DATAProvider_H
