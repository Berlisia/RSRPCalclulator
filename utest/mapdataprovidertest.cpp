#include "MapProvider/MapDataProvider.h"
#include <gtest/gtest.h>
#include <memory>
#include "iostream"

class MapDataProviderTest : public ::testing::Test
{
public:
    MapDataProviderTest()
    {
        mapProvider = std::make_unique<MapDataProvider>();
    }
    void SetUp() override {}
    void TearDown() override {}


    std::unique_ptr<IMapDataProvider> mapProvider;
};

TEST_F(MapDataProviderTest, getPixelHeightTest)
{
    std::pair<int,int> pixelExample = std::make_pair<int, int>(2000,2000);
    unsigned int expextedHeight = 236;
    unsigned int height = mapProvider->pixelHeight(pixelExample);

    EXPECT_TRUE(expextedHeight == height);
}

TEST_F(MapDataProviderTest, coutDistanceTest)
{
    std::pair<int,int> pixelExample1 = std::make_pair<int, int>(2000,2000);
    std::pair<int,int> pixelExample2 = std::make_pair<int, int>(3000,3000);
    unsigned int expectedDistance = 35355;
    unsigned int distance = mapProvider->coutDistance(pixelExample1, pixelExample2);

    EXPECT_TRUE(expectedDistance == distance);
}
