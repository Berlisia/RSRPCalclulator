#include "Worker.h"
#include "RSRP/RsrpCalculation.h"
#include "RSRP/RsrpInitialization.h"
#include "MapProvider/MapDataProvider.h"
#include "AntennaLoss/AntennaLossFileProvider.h"

Worker::Worker()
{
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Thread: " << n << std::endl;
    pool = std::make_unique<ThreadPool>(n-1);
    dataProvider = std::make_shared<MapDataProvider>();
    antennaProvider = std::make_shared<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                                "742266V02_pionowa.csv"); //Tymczasowo
    fakeInit();
    calculateRsrpForSectors();
}

void Worker::doCalculation()
{
    for(unsigned int j = areaCalculation->beginY(); j < areaCalculation->endY(); j++)//y
    {
        for(unsigned int i = areaCalculation->beginX(); i < areaCalculation->endX(); i++)//x
        {
            PixelXY pixel(i,j);
            //executeCalculationForPixel(pixel);
            //std::cout << i << std::endl;
            pool->add(std::bind(&Worker::executeCalculationForPixel, this, pixel), pixel);
        }
    }

    pool->start();
    pool->stop();
}

void Worker::listInCoutRSPR()
{
    for(auto rsrp : RSRP)
    {
        std::cout << rsrp.second << " " << rsrp.first.getX() << " " << rsrp.first.getY() << std::endl;
    }
}

void Worker::fakeInit()
{
    PixelXY possitionOfBaseStation(std::make_pair<int,int>(2000,2000));
    std::shared_ptr<BaseStation> baseStation =
            std::make_shared<BaseStation>(std::move(possitionOfBaseStation.getXy()), 120);

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
    area.push_back(std::make_pair<int,int>(3000,1000));
    area.push_back(std::make_pair<int,int>(1000,3000));
    area.push_back(std::make_pair<int,int>(3000,3000));

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

void Worker::executeCalculationForPixel(PixelXY pixel)
{
    PixelWorker pixelWorker(RSRP, rsrpForSectors, pixel, dataProvider, antennaProvider, *sectors);
    pixelWorker.executeCalculation();
}
