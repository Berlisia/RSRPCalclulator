#include <gtest/gtest.h>
#include "MapProvider/MapDataProvider.h"
#include "AntennaLoss/AntennaLossFileProvider.h"
#include "AntennaLoss/AntennaLossHorizontalCalculator.h"

#include <memory>

class AntenaLossHorizontalCalculatorTest : public ::testing::Test
{
public:
    AntenaLossHorizontalCalculatorTest()
    {
        dataProvider = std::make_unique<MapDataProvider>();
        antennaProvider = std::make_unique<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                                   "742266V02_pionowa.csv");
        calculator = std::make_unique<AntennaLossHorizontalCalculator>(*dataProvider,
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
    std::unique_ptr<AntennaLossHorizontalCalculator> calculator;
};

TEST_F(AntenaLossHorizontalCalculatorTest, calculateHorizontalLossTest_AzimutLessThan180)
{
    std::pair<int,int> fakeReceiver = std::make_pair(2425,2244);
    std::pair<int,int> fakeAntenna = std::make_pair(2579, 1919);
    int fakeAntennaAzimuth = 135;

    calculator->setReceiver(fakeReceiver);
    calculator->setAntenna(fakeAntenna);
    calculator->setAzimuth(fakeAntennaAzimuth);

    float expectedLoss = 23.71;
    float loss = calculator->calculateAntennaLoss();
    EXPECT_EQ(loss, expectedLoss);
}

TEST_F(AntenaLossHorizontalCalculatorTest, calculateHorizontalLossTest_AzimuthMoreThan180)
{
    std::pair<int,int> fakeReceiver = std::make_pair(2425,2244);
    std::pair<int,int> fakeAntenna = std::make_pair(2579, 1919);
    int fakeAntennaAzimuth = 225;

    calculator->setReceiver(fakeReceiver);
    calculator->setAntenna(fakeAntenna);
    calculator->setAzimuth(fakeAntennaAzimuth);

    float expectedLoss = 40.68;
    float loss = calculator->calculateAntennaLoss();
    EXPECT_EQ(loss, expectedLoss);
}

TEST_F(AntenaLossHorizontalCalculatorTest, calculateHorizontalLossTest_AzimuthLessThanAzimuthZeroDeegres)
{
    std::pair<int,int> fakeReceiver = std::make_pair(2425,2244);
    std::pair<int,int> fakeAntenna = std::make_pair(2579, 1919);
    int fakeAntennaAzimuth = 15;

    calculator->setReceiver(fakeReceiver);
    calculator->setAntenna(fakeAntenna);
    calculator->setAzimuth(fakeAntennaAzimuth);

    float expectedLoss = 0.35;
    float loss = calculator->calculateAntennaLoss();
    EXPECT_EQ(loss, expectedLoss);
}
