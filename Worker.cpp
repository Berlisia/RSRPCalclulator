#include "Worker.h"
#include "RSRP/RsrpCalculation.h"
#include "RSRP/RsrpInitialization.h"
#include "MapProvider/MapDataProvider.h"
#include "AntennaLoss/AntennaLossFileProvider.h"
#include "Workers/PixelWorkerForInterference.h"
#include "Workers/PixelWorkerForSNIR.h"
#include "Workers/PixelWorkerForModulation.h"
#include <math.h>

Worker::Worker(DataProvider & p_data) :
    data(p_data), sectors(p_data.sectorControler)
{
    unsigned int n = std::thread::hardware_concurrency();
    pool = std::make_unique<ThreadPool>(n);
    mapDataProvider = std::make_shared<MapDataProvider>();
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
    Receiver receiver = setupReciver(pixel);
    //const PixelWorker pixelWorkerSignal = calculateSignal(receiver);
    PixelWorker pixelWorkerSignal(RSRP, rsrpForSectors, mapDataProvider, *sectors, receiver, data.minValueOfRSRP);
    pixelWorkerSignal.executeCalculation();
    double interference = calculateInterference(pixel, pixelWorkerSignal);
    double snir = calculateSnir(pixel, interference, pixelWorkerSignal.getCurrentSignalPower());

    PixelWorkerForModulation pixelWorkerForModulation;
    pixelWorkerForModulation.calculate(pixel, snir, data.modulation);
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

const Receiver& Worker::setupReciver(const PixelXY& pixel)
{
    Receiver receiver;
    receiver.setPossition(pixel.getXy());
    receiver.setGain(data.receiver.getGain());
    receiver.setOtherLosses(data.receiver.getOtherLosses());
    receiver.setHeight(data.receiver.getHeight());

    return std::move(receiver);
}

const PixelWorker& Worker::calculateSignal(const Receiver& receiver)
{
    PixelWorker pixelWorker(RSRP, rsrpForSectors, mapDataProvider, *sectors, receiver, data.minValueOfRSRP);
    pixelWorker.executeCalculation();
    return std::move(pixelWorker);
}

double Worker::calculateInterference(const PixelXY &pixel, const PixelWorker& pixelWorker)
{
    PixelWorkerForInterference pixelWorkerInt(pixelWorker.getResultFromAllSectors(), *sectors, pixelWorker.getCurrentBand());
    return pixelWorkerInt.calculate(data.interferenceLvl, pixel);
}

double Worker::calculateSnir(const PixelXY &pixel, double intLvl, double signalLvl)
{
    PixelWorkerForSNIR pixelWorkerForSnir;
    return pixelWorkerForSnir.calculate(intLvl, signalLvl, pixel, data.snir);
}
