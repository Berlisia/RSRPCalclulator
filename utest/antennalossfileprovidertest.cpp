#include <gtest/gtest.h>
#include "AntennaLoss/AntennaLossFileProvider.h"
#include "utest/antennalossfileparsermock.h"
#include <memory>

class AntennaLossFileProviderTest : public ::testing::Test
{
public:
    AntennaLossFileProviderTest()
    {
        antennaProider = std::make_unique<AntennaLossFileProvider>("742266V02_pozioma.csv",
                                                                   "742266V02_pionowa.csv");
    }

    void SetUp() override
    {

    }
    void TearDown() override
    {

    }
    std::unique_ptr<IAntennaLossFileProvider> antennaProider;
};

TEST_F(AntennaLossFileProviderTest, getLossFromFileForHorizonalCharacteristic)
{
    int angle = 10;
    float expectedLoss = 0.35;
    float loss = antennaProider->getLossFromFile(angle, Charakteristic::horizontal);
    EXPECT_TRUE(loss == expectedLoss);
}

TEST_F(AntennaLossFileProviderTest, getLossFromFileForVerticalCharacteristic)
{
    int angle = 10;
    float expectedLoss = 26.95;
    float loss = antennaProider->getLossFromFile(angle, Charakteristic::vertical);
    EXPECT_TRUE(loss == expectedLoss);
}


