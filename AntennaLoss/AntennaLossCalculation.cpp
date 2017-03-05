#include "AntennaLossCalculation.h"

AntennaLossCalculation::AntennaLossCalculation(std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                                               SectorsControler & p_sectors) :
    mapDataProvider(p_mapDataProvider), sectors(p_sectors)
{
}

AntennaLossForSectors AntennaLossCalculation::calculate()
{
    std::vector<float> loss;
    for(auto sector : sectors.getVectorOfSectors())
    {
        float lossH = lossHorizontal(sector);
        float lossV = lossVertical(sector);
        loss.push_back(lossH + lossV);
    }
    AntennaLossForSectors lossPtr = std::make_shared<std::vector<float>>(std::move(loss));
    return lossPtr;
}

void AntennaLossCalculation::setReciver(PixelXY p_pixel)
{
    pixel = p_pixel;
}

void AntennaLossCalculation::check(const Sector & sector, AntennaLossHorizontalCalculator &horizontalCalculator)
{
    if(sector.getPossitonOfBaseStation() != horizontalCalculator.getAntennaPossiton())
    {
        horizontalCalculator.setAntenna(sector.getPossitonOfBaseStation());
    }
}

void AntennaLossCalculation::check(const Sector &sector, AntennaLossVerticalCalculator & verticalCalculator)
{
    if(sector.getAntennaHeight() != verticalCalculator.getAntennaHeight())
    {
        verticalCalculator.setAntennaHeight(sector.getAntennaHeight());
    }
}

float AntennaLossCalculation::lossVertical(const Sector &sector)
{
    AntennaLossVerticalCalculator verticalCalculator(mapDataProvider, sector.getAntennaCharacteristic());
    verticalCalculator.setTilt(sector.getAntennaTilt());
    check(sector, verticalCalculator);
    verticalCalculator.setReceiver(pixel.getXy());
    float lossV = verticalCalculator.calculateAntennaLoss();
    return lossV;
}

float AntennaLossCalculation::lossHorizontal(const Sector &sector)
{
    AntennaLossHorizontalCalculator horizontalCalculator(mapDataProvider, sector.getAntennaCharacteristic());
    horizontalCalculator.setAzimuth(sector.getAzimuth());
    check(sector, horizontalCalculator);
    horizontalCalculator.setReceiver(pixel.getXy());
    float lossH = horizontalCalculator.calculateAntennaLoss();
    return lossH;
}
