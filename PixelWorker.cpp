#include "PixelWorker.h"
#include "Pathloss/PathlossCalculation.h"
#include "Pathloss/OkumuraHataPathlossModel.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>

std::mutex PixelWorker::mutex;

PixelWorker::PixelWorker(RSRPForPixel & p_RSRP,
                         RsrpValueForSectorRef p_rsrpSectors,
                         std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                         SectorsControler & p_sectors,
                         Receiver & p_receiver,
                         double p_minValueRSRP) :
    RSRP(p_RSRP), rsrpSectors(p_rsrpSectors), receiver(p_receiver), minValueRSRP(p_minValueRSRP),
    antennaCalculation(AntennaLossCalculation(p_mapDataProvider, p_sectors))
{
    pathlossCalculation = std::make_unique<PathlossCalculation>(p_mapDataProvider, p_sectors, p_receiver);
}

void PixelWorker::executeCalculation()
{
    calculateAntennaLossForOnePixel();
    calculatePathlossForOnePixel(); //wraz z zyskiem anteny

    for (unsigned int i = 0; i < antennaLossFromSectorsPerOnePixel->size(); i++) //for po wszystkich sectorach
    {
        float pathL = pathLossFromSectorsPerOnePixel[i];
        if(!std::isnan(pathL) and !std::isinf(pathL)) //dBm
        {
            float rsrp = rsrpSectors[i] -
                    (*antennaLossFromSectorsPerOnePixel)[i] -
                     pathL +
                     receiver.getGain() - receiver.getOtherLosses();
            if(rsrp > (minValueRSRP))
            {
                rsrpFromSectors.push_back(rsrp);
            }
        }
    }
    if(!rsrpFromSectors.empty())
    {
        float maxValue = findMaxFrom(rsrpFromSectors);
        std::unique_lock<std::mutex> lock(mutex);
        RSRP.vector.push_back(std::pair<PixelXY,float>(receiver.getPossition(), maxValue));
        emit RSRP.rsrpSizeChanged();
    }
}

std::vector<float> &PixelWorker::getResultFromAllSectors()
{
    return rsrpFromSectors;
}

float PixelWorker::findMaxFrom(const std::vector<float> &vector)
{
    auto biggest = std::max_element(std::begin(vector), std::end(vector));
    auto biggestVal = *biggest;
    rsrpFromSectors.erase(biggest);
    return biggestVal;
}

void PixelWorker::calculateAntennaLossForOnePixel()
{
    antennaCalculation.setReciver(receiver.getPossition());
    antennaLossFromSectorsPerOnePixel = antennaCalculation.calculate();
}

void PixelWorker::calculatePathlossForOnePixel()
{
    pathLossFromSectorsPerOnePixel = pathlossCalculation->calculatePathloss();
}
