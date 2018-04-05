#include "PixelWorker.h"
#include "Pathloss/PathlossCalculation.h"
#include "Pathloss/OkumuraHataPathlossModel.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>

std::mutex PixelWorker::mutex;

PixelWorker::PixelWorker(RSRPForPixel& p_RSRP,
                         RsrpValueForSectorRef p_rsrpSectors,
                         std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                         SectorsControler& p_sectors,
                         const Receiver& p_receiver,
                         double p_minValueRSRP) :
    RSRP(p_RSRP), rsrpSectors(p_rsrpSectors), sectorsControler(p_sectors),
    receiver(p_receiver), minValueRSRP(p_minValueRSRP),
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
        double pathL = pathLossFromSectorsPerOnePixel[i];
        if(!std::isnan(pathL) and !std::isinf(pathL)) //dBm
        {
            double rsrp = rsrpSectors[i] - (*antennaLossFromSectorsPerOnePixel)[i] -
                         pathL + receiver.getGain() - receiver.getOtherLosses();
            if(rsrp > (minValueRSRP))
            {
                rsrpFromSectors.push_back(std::pair<int,double>(sectorsControler.getBandIndexFromSector(i), rsrp));
            }
        }
    }
    if(!rsrpFromSectors.empty())
    {
        storeMaxFromRsrpMap();
        std::unique_lock<std::mutex> lock(mutex);
        RSRP.vector.push_back(std::pair<PixelXY,double>(receiver.getPossition(), currentSignalPower));
        emit RSRP.rsrpSizeChanged();
    }
}

const std::vector<std::pair<int, double> >& PixelWorker::getResultFromAllSectors() const
{
    return rsrpFromSectors;
}

void PixelWorker::storeMaxFromRsrpMap()
{
    auto biggest = std::max_element(std::begin(rsrpFromSectors), std::end(rsrpFromSectors),
                                    [] (const auto p1, const auto p2) {return p1.second < p2.second;});
    currentSignalPower = biggest->second;
    currentBand = biggest->first;
    rsrpFromSectors.erase(biggest);
}

int PixelWorker::getCurrentBand() const
{
    return currentBand;
}

double PixelWorker::getCurrentSignalPower() const
{
    return currentSignalPower;
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
