#include <iostream>
#include "RuskiTest/rsrptestcase.h"
#include "RuskiTest/AntennaLossFileParserTest.h"
//#include <gtest/gtest.h>
using namespace std;

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

#include <QApplication>
#include "Image.h"

#include <memory>
#include <iostream>

class CalculateRSRPWithoughtPathLoss
{
public:
    CalculateRSRPWithoughtPathLoss(): max(-300), min(0)
    {
        dataProvider = std::make_unique<MapDataProvider>();
        antennaProvider = std::make_unique<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                                   "742266V02_pionowa.csv");
    }

    std::unique_ptr<IMapDataProvider> dataProvider;
    std::unique_ptr<IAntennaLossFileProvider> antennaProvider;
    std::vector<std::pair<PixelXY, float>> RSRP;
    std::vector<std::pair<int,int>> area;
    float max;
    float min;

    void cos()
    {
        PixelXY possitionOfBaseStation(std::make_pair<int,int>(1018,1018));
        BaseStation baseStation(possitionOfBaseStation.getXy(),120);

        Antenna antenna1(30,1,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");
        Antenna antenna2(20,2,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");
        Antenna antenna3(10,3,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");

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
        //Area calculation !!!!

        area.push_back(std::make_pair<int,int>(1000,1000));
        area.push_back(std::make_pair<int,int>(1026,1000));
        area.push_back(std::make_pair<int,int>(1000,1026));
        area.push_back(std::make_pair<int,int>(1026,1026));

        //RSRP
        RsrpInitialization rsrpInit;
        std::unique_ptr<IRsrpCalculation> rsrpCalculator(std::make_unique<RsrpCalculation>(rsrpInit));
        std::vector<float> rsrpFromSectors;
        for(auto sec : sector)
        {
            rsrpFromSectors.push_back(rsrpCalculator->calculateRsrp(sec));
        }

        //HorizontalLoss
        std::unique_ptr<AntennaLossHorizontalCalculator> antennaLossCalculator(
                    std::make_unique<AntennaLossHorizontalCalculator>(*dataProvider,
                                                                      *antennaProvider));
        antennaLossCalculator->setAntenna(baseStation.getPossition());

        //VerticalLoss
        std::unique_ptr<AntennaLossVerticalCalculator> antennaLossVCalculator =
                std::make_unique<AntennaLossVerticalCalculator>(*dataProvider,
                                                                *antennaProvider);
        antennaLossVCalculator->setAntenna(baseStation.getPossition());
        antennaLossVCalculator->setAntennaHeight(baseStation.getAntennaHeight());

        std::vector<float> antennaHorizontalLoss;
        std::vector<float> antennaVerticalLoss;
        std::vector<float> endedRSRP;

        for(unsigned int j = area[0].first; j < area[3].second; j++)//y
        {
            for(unsigned int i = area[0].first; i < area[3].first; i++)//x
            {
                Receiver receiver(std::make_pair<int,int>(i,j));
                antennaLossCalculator->setReceiver(receiver.getPossition().getXy());
                antennaLossVCalculator->setReceiver(receiver.getPossition().getXy());

                for(auto sec : sector)
                {
                    antennaLossCalculator->setAzimuth(sec.getAzimuth());
                    float lossH = antennaLossCalculator->calculateAntennaLoss();
                    antennaHorizontalLoss.push_back(lossH);

                    antennaLossVCalculator->setTilt(sec.getAntennaTilt());
                    float lossV = antennaLossVCalculator->calculateAntennaLoss();
                    antennaVerticalLoss.push_back(lossV);
                }

                for(unsigned int i = 0; i < 3; i++)
                {
                    endedRSRP.push_back(rsrpFromSectors[i] - antennaHorizontalLoss[i] - antennaVerticalLoss[i]);
                }

                float maxValue = rsrpCalculator->findMaxRsrpFromSectors(endedRSRP);
                RSRP.push_back(std::pair<PixelXY,float>(receiver.getPossition(), maxValue));

                if(max < maxValue) max = maxValue;
                if(min > maxValue) min = maxValue;

                antennaHorizontalLoss.clear();
                antennaVerticalLoss.clear();
                endedRSRP.clear();
            }
        }


    }
};

int main(int argc, char *argv[])
{
//    RsrpTestCase testRsrp;
//    testRsrp.rsrpCalculationTest();

    QApplication a(argc, argv);

    CalculateRSRPWithoughtPathLoss calk;
    calk.cos();

    Image image(3802, 3942);

    image.setMaxValue(calk.max);
    image.setMinValue(calk.min);
    image.calculateFactor();

    for(auto pixel : calk.RSRP)
    {
        QPoint point(pixel.first.getX(), pixel.first.getY());
        QColor color = image.generateColor(pixel.second);
        QRgb rgb = color.rgb();
        image.paintPixel(point, rgb);
    }


    image.show();

//    //gtest wariant
//    ::testing::InitGoogleTest(&argc, argv);
//      return RUN_ALL_TESTS();

      return a.exec();
}
