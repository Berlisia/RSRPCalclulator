#include "PixelWorker.h"
#include "Pathloss/PathlossCalculation.h"
#include "Pathloss/OkumuraHataPathlossModel.h"
#include <algorithm>
#include <iostream>
#include <fstream>

std::mutex PixelWorker::mutex;

PixelWorker::PixelWorker(RSRPForPixel & p_RSRP,
                         RsrpValueForSectorRef p_rsrpSectors,
                         std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                         std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                         SectorsControler & p_sectors,
                         Receiver & p_receiver) :
    RSRP(p_RSRP), rsrpSectors(p_rsrpSectors), receiver(p_receiver),
    antennaCalculation(AntennaLossCalculation(p_mapDataProvider, p_antennaLossDataProvider, p_sectors))
{
    pathlossCalculation = std::make_unique<PathlossCalculation>(p_mapDataProvider, p_sectors, p_receiver);
}

void PixelWorker::executeCalculation()
{
    std::vector<float> rsrpFromSectors;
    calculateAntennaLossForOnePixel();
    calculatePathlossForOnePixel();

    for (unsigned int i = 0; i < antennaLossFromSectorsPerOnePixel->size(); i++) //for po wszystkich sectorach
    {
        rsrpFromSectors.push_back(rsrpSectors[i] -
                                 (*antennaLossFromSectorsPerOnePixel)[i] -
                                  pathLossFromSectorsPerOnePixel[i]
                                  );
    }
    float maxValue = findMaxFrom(rsrpFromSectors);
    std::unique_lock<std::mutex> lock(mutex);
    RSRP.push_back(std::pair<PixelXY,float>(receiver.getPossition(), maxValue));
//    std::cout << receiver.getPossition().getX() << " "
//              << receiver.getPossition().getY() << " "
//              << maxValue << std::endl;
}

float PixelWorker::findMaxFrom(const std::vector<float> &vector)
{
    auto biggest = std::max_element(std::begin(vector), std::end(vector));
    return *biggest;
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
