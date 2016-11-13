#include "Worker.h"
#include "RSRP/RsrpCalculation.h"
#include "RSRP/RsrpInitialization.h"
#include "MapProvider/MapDataProvider.h"
#include "AntennaLoss/AntennaLossFileProvider.h"

Worker::Worker(DataProvider & p_data) :
    data(p_data), sectors(p_data.sectorControler)
{
    unsigned int n = std::thread::hardware_concurrency();
    pool = std::make_unique<ThreadPool>(3);

    dataProvider = std::make_shared<MapDataProvider>();
    antennaProvider = std::make_shared<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                                "742266V02_pionowa.csv"); //Tymczasowo
    fakeInit();
}

void Worker::doCalculation()
{
    calculateRsrpForSectors();
    for(unsigned int j = areaCalculation->beginY(); j < areaCalculation->endY(); j++)//y
    {
        for(unsigned int i = areaCalculation->beginX(); i < areaCalculation->endX(); i++)//x
        {
            PixelXY pixel(i,j);
            if(!isBaseStation(pixel))
                pool->add(std::bind(&Worker::executeCalculationForPixel, this, pixel), pixel);
        }
    }

    pool->start();
    pool->stop();

    std::fstream plik;
    plik.open("wartosci.txt", std::ios::out );
    if( plik.good() == true )
    {
        for(auto r : RSRP)
    {
        plik << r.first.getX() << " "
              << r.first.getY() << " "
              << r.second;
        plik << "\n";
        }
    }
    plik.close();

    data.getRsrp(RSRP);
    if(!data.rsrp.empty())
        emit done();
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
    std::vector<std::pair<int,int>> area;
    area.push_back(std::make_pair<int,int>(500,500));
    area.push_back(std::make_pair<int,int>(1500,500));
    area.push_back(std::make_pair<int,int>(500,1500));
    area.push_back(std::make_pair<int,int>(1500,1500));

    areaCalculation = std::make_unique<AreaCalculation>(area);
}

void Worker::calculateRsrpForSectors()
{
    if(sectors)
    {
        RsrpInitialization rsrpInit;
        std::unique_ptr<IRsrpCalculation> rsrpCalculator(std::make_unique<RsrpCalculation>(rsrpInit));
        for(auto sec : sectors->getVectorOfSectors())
        {
            rsrpForSectors.push_back(rsrpCalculator->calculateRsrp(sec));
        }
    }
}

void Worker::executeCalculationForPixel(PixelXY pixel)
{
    Receiver receiver;
    receiver.setPossition(pixel.getXy());
    receiver.setHeight(1); //jakos pobrać i globalnie dać!
    PixelWorker pixelWorker(RSRP, rsrpForSectors, dataProvider, antennaProvider, *sectors, receiver);
    pixelWorker.executeCalculation();
}

bool Worker::isBaseStation(PixelXY pixel)
{
    bool isBase = false;
    for(auto station : data.baseStations)
    {
        if(pixel.getX() == station->getPossition().first and
                pixel.getY() == station->getPossition().second)
        {
            isBase = true;
        }
    }
    return isBase;
}
