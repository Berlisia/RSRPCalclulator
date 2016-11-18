#include "PathlossCalculation.h"
#include "OkumuraHataPathlossModel.h"
#include "Cost231HataModel.h"
#include <memory>
#include <cmath>
#include <iostream>

PathlossCalculation::PathlossCalculation(std::shared_ptr<IMapDataProvider> p_mapProvider,
                                         SectorsControler &p_sectors,
                                         Receiver &p_receiver) :
    mapProvider(p_mapProvider), sectors(p_sectors), receiver(p_receiver)
{
}

std::vector<float> PathlossCalculation::calculatePathloss()
{
    std::vector<float> loss;
    for(auto sector : sectors.getVectorOfSectors())
    {
        Model model = choosePropagarionModel(sector);
        Pathloss pathloss = 0;
        switch(model)
        {
        case Model::OkumuraHata:
            pathloss = okumuraCalculation(sector);
            break;
        case Model::Cost231Hata:
            pathloss = costCalculation(sector);
            break;
        default:
            break;
        }
        loss.push_back(pathloss);
    }
    return std::move(loss);
}

float PathlossCalculation::effectiveBAntennaHeight(Sector const& sector)
{
    float mediumHeight = mapProvider->coutMediumHeightBetwenTwoPixels(sector.getPossitonOfBaseStation(), receiver.getPossition().getXy(), 35);

    float h = mapProvider->pixelHeight(sector.getPossitonOfBaseStation());
    float height = sector.getAntennaHeight() + h - mediumHeight;

    if(height < 30)
    {
        h = mapProvider->pixelHeight(receiver.getPossition().getXy());
        height = sector.getAntennaHeight() + h - mediumHeight;
    }
    return height;
}
void PathlossCalculation::setUpParameters(PathlossModel & model, Sector const& sector)
{
    model.changeCarrierFrequency(sector.getFrequency());
    model.changeEffectiveMSAntennaHeight(receiver.getHeight());
    model.changeEffectiveBSAntennaHeight(effectiveBAntennaHeight(sector));
    //model.changeEffectiveBSAntennaHeight(sector.getAntennaHeight());
    model.changeDistance((mapProvider->coutDistance(sector.getPossitonOfBaseStation(),
                                                   receiver.getPossition().getXy())*0.001)); //km!!!!
    model.changeCurrentEnvironment(sector.getEnvironment());
}

Model PathlossCalculation::choosePropagarionModel(Sector const& sector)
{
    return sector.getModel();
}

Pathloss PathlossCalculation::okumuraCalculation(Sector const& sector)
{
    if(!okumuryModel)
    {
        okumuryModel = std::make_unique<OkumuraHataPathlossModel>();
    }
    setUpParameters(*okumuryModel, sector);
    Pathloss pathloss = okumuryModel->pathloss();
    return pathloss;
}

Pathloss PathlossCalculation::costCalculation(Sector const& sector)
{
    if(!hataModel)
    {
        hataModel = std::make_unique<Cost231HataModel>();
    }
    setUpParameters(*hataModel, sector);
    Pathloss pathloss = hataModel->pathloss();
    return pathloss;
}


