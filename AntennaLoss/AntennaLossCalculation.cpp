#include "AntennaLossCalculation.h"

AntennaLossCalculation::AntennaLossCalculation(std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                                               std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                                               SectorsControler & p_sectors) :
    mapDataProvider(p_mapDataProvider), antennaLossDataProvider(p_antennaLossDataProvider), sectors(p_sectors)
{
    horizontalCalculator = std::make_shared<AntennaLossHorizontalCalculator>(mapDataProvider, antennaLossDataProvider);
    verticalCalculator = std::make_shared<AntennaLossVerticalCalculator>(mapDataProvider, antennaLossDataProvider);
}

AntennaLossForSectors AntennaLossCalculation::calculate()
{
    std::vector<float> loss;
    for(auto sector : *sectors.getVectorOfSectors())
    {
        check(sector);

        horizontalCalculator->setAzimuth(sector.getAzimuth());
        float lossH = horizontalCalculator->calculateAntennaLoss();

        verticalCalculator->setTilt(sector.getAntennaTilt());
        float lossV = verticalCalculator->calculateAntennaLoss();
        loss.push_back(lossH + lossV);
    }
    AntennaLossForSectors lossPtr = std::make_shared<std::vector<float>>(std::move(loss));
    return lossPtr;
}

void AntennaLossCalculation::setReciver(PixelXY pixel)
{
    horizontalCalculator->setReceiver(pixel.getXy());
    verticalCalculator->setReceiver(pixel.getXy());
}

void AntennaLossCalculation::check(Sector & sector)
{
    if(sector.getPossitonOfBaseStation() != horizontalCalculator->getAntennaPossiton())
    {
        horizontalCalculator->setAntenna(sector.getPossitonOfBaseStation());
    }
    if(sector.getAntennaHeight() != verticalCalculator->getAntennaHeight())
    {
        verticalCalculator->setAntennaHeight(sector.getAntennaHeight());
    }
}
