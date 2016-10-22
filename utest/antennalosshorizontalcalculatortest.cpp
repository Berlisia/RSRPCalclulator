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

TEST_F(AntenaLossHorizontalCalculatorTest, calculateHorizontalLossTest)
{
    std::pair<int,int> fakeReceiver = std::make_pair(2425,2244);
    std::pair<int,int> fakeAntenna = std::make_pair(2579, 1919);

    calculator->setReceiver(fakeReceiver);
    calculator->setAntenna(fakeAntenna);

    float expectedLoss = 2.01;
    float loss = calculator->calculateAntennaLoss();
    EXPECT_EQ(loss, expectedLoss);
}
