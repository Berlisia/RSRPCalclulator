#include <gtest/gtest.h>
#include "Core/PixelFinder.h"

class PixelFinderTest : public ::testing::Test
{
public:
    PixelFinderTest()
    {
        pixelFinder = std::make_unique<PixelFinder>(area);
    }

    void SetUp() override
    {
        area.push_back(PixelPoint(std::make_pair<int,int>(1000,1000)));
        area.push_back(PixelPoint(std::make_pair<int,int>(2000,1000)));
        area.push_back(PixelPoint(std::make_pair<int,int>(1000,2000)));
        area.push_back(PixelPoint(std::make_pair<int,int>(2000,2000)));
    }
    void TearDown() override
    {

    }

    std::unique_ptr<PixelFinder> pixelFinder;
    vectorOfPixels area;
};

TEST_F(PixelFinderTest, changePixel_GoodPixel)
{
    PixelPoint pixel(std::make_pair<int,int>(1024,1999));

    pixelFinder->changePixel(&pixel);
    EXPECT_TRUE(pixel, pixelFinder->getPixel());
}
