#include "Worker.h"
#include "RSRP/RsrpCalculation.h"
#include "RSRP/RsrpInitialization.h"
#include "MapProvider/MapDataProvider.h"
#include "AntennaLoss/AntennaLossFileProvider.h"
#include "Workers/PixelWorkerForInterference.h"
#include "Workers/PixelWorkerForSNIR.h"
#include <math.h>

Worker::Worker(DataProvider & p_data) :
    data(p_data), sectors(p_data.sectorControler)
{
    unsigned int n = std::thread::hardware_concurrency();
    //n = 1;
    pool = std::make_unique<ThreadPool>(n);

    mapDataProvider = std::make_shared<MapDataProvider>();
    //antennaProvider = std::make_shared<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                               // "742266V02_pionowa.csv"); //Tymczasowo
    //fakeInit();
}

void Worker::doCalculation()
{
    if (!data.areaPixels.size()) // core dump when user click run without selected sector
        return;

    calculateRsrpForSectors();
    areaCalculation = std::make_unique<AreaCalculation>(data.areaPixels);
    for(auto j = areaCalculation->beginY(); j < areaCalculation->endY(); j++)//y
    {
        for(auto i = areaCalculation->beginX(); i < areaCalculation->endX(); i++)//x
        {
            PixelXY pixel(i,j);
            if(!isBaseStation(pixel))
                pool->add(std::bind(&Worker::executeCalculationForPixel, this, pixel), pixel);
        }
    }

    pool->start();
    emit poolStarted();
    pool->stop();

    saveInFile(RSRP.vector, "signal.txt");
    saveInFile(data.interferenceLvl, "interference.txt");
    saveInFile(data.snir, "snir.txt");

    data.getRsrp(RSRP.vector);
    if(!data.rsrp.vector.empty())
        emit done();
}

void Worker:: listInCoutRSPR()
{
    for(auto rsrp : RSRP.vector)
    {
        std::cout << rsrp.second << " " << rsrp.first.getX() << " " << rsrp.first.getY() << std::endl;
    }
}

int Worker::getQueueSize() const
{
    return 0; //pool->getTaskQueueSize();
}

std::shared_ptr<IMapDataProvider> Worker::getMapDataProvider() const
{
    return mapDataProvider;
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
    receiver.setGain(data.receiver.getGain());
    receiver.setOtherLosses(data.receiver.getOtherLosses());
    receiver.setHeight(data.receiver.getHeight());

    PixelWorker pixelWorker(RSRP, rsrpForSectors, mapDataProvider, *sectors, receiver, data.minValueOfRSRP);
    pixelWorker.executeCalculation();

    PixelWorkerForInterference pixelWorkerInt(pixelWorker.getResultFromAllSectors(), *sectors, pixelWorker.getCurrentBand());
    pixelWorkerInt.calculate(data.interferenceLvl, pixel);

    PixelWorkerForSNIR pixelWorkerForSnir;
    pixelWorkerForSnir.calculate(pixelWorkerInt.getInterferenceLvl(), pixelWorker.getCurrentSignalPower(), pixel, data.snir);
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

void Worker::deleteNanValue()
{
    RSRP.vector.erase(std::remove_if(RSRP.vector.begin(), RSRP.vector.end(),
                              [](const std::pair<PixelXY,double> & dataObj) {
                                    return dataObj.second == std::nanf("");
    }));
}

void Worker::saveInFile(const std::vector<std::pair<PixelXY, double> >& vector, std::string name)
{
    std::fstream plik;
    plik.open(name.c_str(), std::ios::out );
    if( plik.good() == true )
    {
        for(auto r : vector)
        {
            plik << r.first.getX() << " "
                  << r.first.getY() << " "
                  << r.second;
            plik << "\n";
        }
    }
    plik.close();
}
