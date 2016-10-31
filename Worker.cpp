#include "Worker.h"
#include "RSRP/RsrpCalculation.h"
#include "RSRP/RsrpInitialization.h"
#include "MapProvider/MapDataProvider.h"
#include "AntennaLoss/AntennaLossFileProvider.h"

Worker::Worker()
{
    pool = std::make_unique<ThreadPool>(1024);
    dataProvider = std::make_shared<MapDataProvider>();
    antennaProvider = std::make_shared<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                               "742266V02_pionowa.csv"); //Tymczasowo
}

void Worker::doCalculation()
{
    for(unsigned int j = areaCalculation->beginY(); j < areaCalculation->endY(); j++)//y
    {
        for(unsigned int i = areaCalculation->beginX(); i < areaCalculation->endX(); i++)//x
        {
            PixelWorker pixelWorker(RSRP, rsrpForSectors, PixelXY(i,j), dataProvider, antennaProvider, *sectors);
            pool->add(std::bind(&PixelWorker::executeCalculationForPixel, pixelWorker));
        }
    }

    pool->start();
}

void Worker::fakeInit()
{
    PixelXY possitionOfBaseStation(std::make_pair<int,int>(1018,1018));
    BaseStation baseStation(possitionOfBaseStation.getXy(), 120);

    Antenna antenna1(30,1,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");
    Antenna antenna2(20,2,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");
    Antenna antenna3(10,3,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");

    std::vector<Sector> sector
    {
        Sector(antenna1, baseStation),
        Sector(antenna2, baseStation),
        Sector(antenna3, baseStation)
    };

    sector[0].setBandwidth(10.0);
    sector[1].setBandwidth(15.0);
    sector[2].setBandwidth(20.0);

    sector[0].setAzimuth(135);
    sector[1].setAzimuth(225);
    sector[2].setAzimuth(350);

    sectors = std::make_shared<SectorsControler>(sector);

    std::vector<std::pair<int,int>> area;
    area.push_back(std::make_pair<int,int>(1000,1000));
    area.push_back(std::make_pair<int,int>(1026,1000));
    area.push_back(std::make_pair<int,int>(1000,1026));
    area.push_back(std::make_pair<int,int>(1026,1026));

    areaCalculation = std::make_unique<AreaCalculation>(area);
}

void Worker::calculateRsrpForSectors()
{
    if(sectors)
    {
        RsrpInitialization rsrpInit;
        std::unique_ptr<IRsrpCalculation> rsrpCalculator(std::make_unique<RsrpCalculation>(rsrpInit));
        for(auto sec : *sectors->getVectorOfSectors())
        {
            rsrpForSectors.push_back(rsrpCalculator->calculateRsrp(sec));
        }
    }
}
