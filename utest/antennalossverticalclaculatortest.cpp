#include <gtest/gtest.h>
#include "AntennaLoss/AntennaLossVerticalCalculator.h"
#include "AntennaLoss/AntennaLossFileProvider.h"
#include "MapProvider/MapDataProvider.h"

#include <memory>

class AnrennaLossVerticalCalculatorTest : public ::testing::Test
{
public:
    AnrennaLossVerticalCalculatorTest()
    {
        dataProvider = std::make_unique<MapDataProvider>();
        antennaProvider = std::make_unique<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                                   "742266V02_pionowa.csv");
        calculator = std::make_unique<AntennaLossVerticalCalculator>(*dataProvider,
                                                                     *antennaProvider);
    }

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    std::unique_ptr<IMapDataProvider> dataProvider;
    std::unique_ptr<IAntennaLossFileProvider> antennaProvider;
    std::unique_ptr<AntennaLossVerticalCalculator> calculator;
};

TEST_F(AnrennaLossVerticalCalculatorTest, calculateAntennaLoss_UEUnderMainBeam) //pod
{
    std::pair<int,int> fakeReceiver = std::make_pair(2425,2244);
    std::pair<int,int> fakeAntenna = std::make_pair(2579, 1919);

    calculator->setReceiver(fakeReceiver);
    calculator->setAntenna(fakeAntenna);
    calculator->setAntennaHeight(170);
    calculator->setTilt(1);

    float expectedLoss = 0.23;
    float loss = calculator->calculateAntennaLoss();
    EXPECT_EQ(loss, expectedLoss);
}

TEST_F(AnrennaLossVerticalCalculatorTest, calculateAntennaLoss_UEAboveMainBeam) //nad
{
    std::pair<int,int> fakeReceiver = std::make_pair(1000,1000);
    std::pair<int,int> fakeAntenna = std::make_pair(1000, 1300);

    calculator->setReceiver(fakeReceiver);
    calculator->setAntenna(fakeAntenna);
    calculator->setAntennaHeight(160);
    calculator->setTilt(4);

    float expectedLoss = 0.73;
    float loss = calculator->calculateAntennaLoss();
    EXPECT_EQ(loss, expectedLoss);
}

