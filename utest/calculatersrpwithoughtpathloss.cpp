#include <gtest/gtest.h>

#include "Core/BaseStation.h"
#include "Core/Antenna.h"
#include "Core/SectorsControler.h"
#include "Core/Receiver.h"

#include "MapProvider/MapDataProvider.h"
#include "AntennaLoss/AntennaLossFileProvider.h"

#include "RSRP/RsrpInitialization.h"
#include "RSRP/RsrpCalculation.h"
#include "AntennaLoss/AntennaLossHorizontalCalculator.h"
#include "AntennaLoss/AntennaLossVerticalCalculator.h"

#include "Image.h"

#include <memory>
#include <iostream>

class CalculateRSRPWithoughtPathLoss : public ::testing::Test
{
public:
    CalculateRSRPWithoughtPathLoss()
    {
        dataProvider = std::make_unique<MapDataProvider>();
        antennaProvider = std::make_unique<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                                   "742266V02_pionowa.csv");
    }

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }


    std::unique_ptr<IMapDataProvider> dataProvider;
    std::unique_ptr<IAntennaLossFileProvider> antennaProvider;
};

TEST_F(CalculateRSRPWithoughtPathLoss, ForOneAntennaBaseAnd3SectorsAndOnePixel)
{
    PixelXY possitionOfBaseStation(std::make_pair<int,int>(2579,1919));
    BaseStation baseStation(possitionOfBaseStation.getXy(),120);

    Antenna antenna1(30,1,1800);
    Antenna antenna2(20,2,1800);
    Antenna antenna3(10,3,1800);

    std::vector<Sector> sector
    {
        Sector(antenna1, baseStation),
        Sector(antenna2, baseStation),
        Sector(antenna3, baseStation)
    };

    sector[0].setBandwidth(10.0);
    sector[1].setBandwidth(15.0);
    sector[2].setBandwidth(20.0);

    sector[0].setAzimuth(135);
    sector[1].setAzimuth(225);
    sector[2].setAzimuth(350);

    SectorsControler sectorsControler(sector);
    Receiver receiver(std::make_pair<int,int> (2425,2244));

    //RSRP
    RsrpInitialization rsrpInit;
    std::unique_ptr<IRsrpCalculation> rsrpCalculator(std::make_unique<RsrpCalculation>(rsrpInit));
    std::vector<float> rsrpFromSectors;
    for(auto sec : sector)
    {
        rsrpFromSectors.push_back(rsrpCalculator->calculateRsrp(sec));
    }

    for(auto d : rsrpFromSectors)
    {
        std::cout << d << std::endl;
    }

    //HorizontalLoss
    std::unique_ptr<AntennaLossHorizontalCalculator> antennaLossCalculator(
                std::make_unique<AntennaLossHorizontalCalculator>(*dataProvider,
                                                                  *antennaProvider));
    antennaLossCalculator->setReceiver(receiver.getPossition().getXy());
    antennaLossCalculator->setAntenna(baseStation.getPossition());
    std::vector<float> antennaHorizontalLoss;
    for(auto sec : sector)
    {
        antennaLossCalculator->setAzimuth(sec.getAzimuth());
        float loss = antennaLossCalculator->calculateAntennaLoss();
        antennaHorizontalLoss.push_back(loss);
    }

    for(auto d : antennaHorizontalLoss)
    {
        std::cout << d << std::endl;
    }

    //VerticalLoss
    antennaLossCalculator.reset();
    std::unique_ptr<AntennaLossVerticalCalculator> antennaLossVCalculator =
            std::make_unique<AntennaLossVerticalCalculator>(*dataProvider,
                                                            *antennaProvider);
    antennaLossVCalculator->setReceiver(receiver.getPossition().getXy());
    antennaLossVCalculator->setAntenna(baseStation.getPossition());
    antennaLossVCalculator->setAntennaHeight(baseStation.getAntennaHeight());
    std::vector<float> antennaVerticalLoss;
    for(auto sec : sector)
    {
        antennaLossVCalculator->setTilt(sec.getAntennaTilt());
        float loss = antennaLossVCalculator->calculateAntennaLoss();
        antennaVerticalLoss.push_back(loss);
    }

    for(auto d : antennaVerticalLoss)
    {
        std::cout << d << std::endl;
    }

    std::vector<float> endedLoss;
    for(unsigned int i = 0; i < 3; i++)
    {
        endedLoss.push_back(rsrpFromSectors[i] - antennaHorizontalLoss[i] - antennaVerticalLoss[i]);
    }

    for(auto rsrp : endedLoss)
    {
        std::cout << rsrp << std::endl;
    }
}

TEST_F(CalculateRSRPWithoughtPathLoss, ForOneAntennaBaseAnd3SectorsWhithChangingPixels)
{

}

