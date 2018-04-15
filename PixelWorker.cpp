#include "PixelWorker.h"
#include "Pathloss/PathlossCalculation.h"
#include "Pathloss/OkumuraHataPathlossModel.h"
#include "RSRP/RsrpInitialization.h"
#include "Common/Units.h"

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
            double rsrp = rsrpSectors[i].second - (*antennaLossFromSectorsPerOnePixel)[i] -
                         pathL + receiver.getGain() - receiver.getOtherLosses();
            //if(rsrp > (minValueRSRP))
            {
                auto numberOfPrb = rsrpSectors[i].first;
                rsrpFromSectors.push_back({numberOfPrb ,sectorsControler.getBandIndexFromSector(i), rsrp});
            }
        }
    }
    if(!rsrpFromSectors.empty())
    {
        storeMaxFromRsrpMap();
        std::unique_lock<std::mutex> lock(mutex);
        RSRP.vector.push_back(std::pair<PixelXY,double>(receiver.getPossition(), currentSignalPower.second));
        emit RSRP.rsrpSizeChanged();
    }
}

const std::vector<PrbBandAndSignalStrengeMapping>& PixelWorker::getResultFromAllSectors() const
{
    return rsrpFromSectors;
}

void PixelWorker::storeMaxFromRsrpMap()
{
    auto biggest = std::max_element(std::begin(rsrpFromSectors), std::end(rsrpFromSectors),
                                    [] (const auto p1, const auto p2) {return p1.signalStrenge < p2.signalStrenge;});
    currentSignalPower = std::pair<int,double>(biggest->prbNumber, biggest->signalStrenge);
    currentBand = biggest->bandIndex;
    rsrpFromSectors.erase(biggest);
}

int PixelWorker::getCurrentBand() const
{
    return currentBand;
}

const std::pair<int,double> PixelWorker::getCurrentSignalPower() const
{
    const auto signalPowerInWat = std::pair<int,double>(currentSignalPower.first, dBmToW(currentSignalPower.second));
    return signalPowerInWat;
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
