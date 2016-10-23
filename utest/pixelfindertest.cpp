#include <gtest/gtest.h>
#include "Core/PixelFinder.h"
#include "Core/AreaCalculation.h"
#include <iostream>

class PixelFinderTest : public ::testing::Test
{
public:
    PixelFinderTest() :
        base(BaseStation()),
        antenna(Antenna(20,0,1800)),
        sec1(Sector(antenna, base)),
        sec2(Sector(antenna, base)),
        sec3(Sector(antenna, base))
    {
        area.push_back(std::make_pair<int,int>(1000,1000));
        area.push_back(std::make_pair<int,int>(2000,1000));
        area.push_back(std::make_pair<int,int>(1000,2000));
        area.push_back(std::make_pair<int,int>(2000,2000));

        areaCalc = std::make_unique<AreaCalculation>(area);

        sec1.setBandwidth(10.0);
        sec2.setBandwidth(15.0);
        sec3.setBandwidth(20.0);

        std::vector<Sector> sectors
        {
            sec1, sec2, sec3
        };
        sectorControler = std::make_unique<SectorsControler>(sectors);
        pixelFinder = std::make_unique<PixelFinder>(*areaCalc, *sectorControler);
    }

    void SetUp() override
    {
    }
    void TearDown() override
    {

    }

    BaseStation base;
    Antenna antenna;
    Sector sec1;
    Sector sec2;
    Sector sec3;

    std::vector<std::pair<int,int>> area;
    std::unique_ptr<AreaCalculation> areaCalc;
    std::unique_ptr<SectorsControler> sectorControler;
    std::unique_ptr<PixelFinder> pixelFinder;
};

TEST_F(PixelFinderTest, changePixel_GoodPixel)
{
    std::unique_ptr<PixelPoint> pixel =
            std::make_unique<PixelPoint>(std::make_pair<int,int>(1024,1999));
    PixelPoint expectedPixel(std::make_pair<int,int>(1024,1999));

    pixelFinder->changePixel(std::move(pixel));
    EXPECT_EQ(expectedPixel.getX(), pixelFinder->getPixel().first);
    EXPECT_EQ(expectedPixel.getY(), pixelFinder->getPixel().second);
}
TEST_F(PixelFinderTest, changePixel_BadPixel)
{
    std::unique_ptr<PixelPoint> pixel =
            std::make_unique<PixelPoint>(std::make_pair<int,int>(102,300));
    PixelPoint expectedPixel(std::make_pair<int,int>(1024,1999));

    pixelFinder->changePixel(std::move(pixel));
    EXPECT_FALSE(expectedPixel.getX() == pixelFinder->getPixel().first);
    EXPECT_FALSE(expectedPixel.getY() == pixelFinder->getPixel().second);
}
