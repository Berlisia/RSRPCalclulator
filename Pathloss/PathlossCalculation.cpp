#include "PathlossCalculation.h"
#include "OkumuraHataPathlossModel.h"
#include "Cost231HataModel.h"
#include <memory>
#include <cmath>

PathlossCalculation::PathlossCalculation(std::shared_ptr<IMapDataProvider> p_mapProvider,
                                         SectorsControler &p_sectors,
                                         Receiver &p_receiver) :
    mapProvider(p_mapProvider), sectors(p_sectors), receiver(p_receiver)
{
}

std::vector<float> PathlossCalculation::calculatePathloss()
{
    std::vector<float> loss;
    std::unique_ptr<PathlossModel> okumuryModel = std::make_unique<OkumuraHataPathlossModel>();
    std::unique_ptr<PathlossModel> hataModel = std::make_unique<Cost231HataModel>();
    for(auto sector : sectors.getVectorOfSectors())
    {
        Pathloss pathloss = 0;
        if(sector.getFrequency() > 1500)
        {
            setUpParameters(*hataModel, sector);
            pathloss = hataModel->pathloss();
        }
        else
        {
            setUpParameters(*okumuryModel, sector);
            pathloss = okumuryModel->pathloss();
        }
        loss.push_back(pathloss);
    }
    return std::move(loss);
}

float PathlossCalculation::effectiveBAntennaHeight(Sector & sector)
{
    std::pair<int,int> vector(sector.getPossitonOfBaseStation().first - receiver.getPossition().getX(),
                              sector.getPossitonOfBaseStation().second - receiver.getPossition().getY());
    float interval = mapProvider->coutDistance(sector.getPossitonOfBaseStation(),
                                               receiver.getPossition().getXy()) / 25;

    float nextHopX = vector.first / interval;
    float nextHopY = vector.second / interval;

    std::vector<float> height;
    float x = sector.getPossitonOfBaseStation().first;
    float y = sector.getPossitonOfBaseStation().second;
    for(int i = 0; i < interval; i++)
    {
        x = x + nextHopX;
        y = y + nextHopY;
        std::pair<int,int> px(std::round(x), std::round(y));
        height.push_back(mapProvider->pixelHeight(px));
    } //+ ostatni
    float sum = 0;
    for(auto h : height)
    {
        sum = sum + h;
    }
    sum = sum/height.size();
    float h = mapProvider->pixelHeight(sector.getPossitonOfBaseStation());
    sum = sector.getAntennaHeight() + h - sum;
    return sum;
}

void PathlossCalculation::setUpParameters(PathlossModel & model, Sector & sector)
{
    model.changeCarrierFrequency(sector.getFrequency());
    //model.changeEffectiveBSAntennaHeight(effectiveBAntennaHeight(sector)); //TODO Potem z  srednią wysokości
    model.changeEffectiveBSAntennaHeight(sector.getAntennaHeight());
    model.changeDistance((mapProvider->coutDistance(sector.getPossitonOfBaseStation(),
                                                   receiver.getPossition().getXy())*0.001)); //km!!!!
    model.changeEffectiveMSAntennaHeight(receiver.getHeight());// +
                                         //mapProvider->pixelHeight(receiver.getPossition().getXy()));
    model.changeCurrentEnvironment(Environment::RuralAera);
}


