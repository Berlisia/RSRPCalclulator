#ifndef ANTENNALOSSCALCULATION_H
#define ANTENNALOSSCALCULATION_H
#include "AntennaLossHorizontalCalculator.h"
#include "AntennaLossVerticalCalculator.h"
#include "Core/SectorsControler.h"

#include <memory>

typedef std::shared_ptr<std::vector<float>> AntennaLossForSectors;

class AntennaLossCalculation
{
public:
    AntennaLossCalculation(std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                           SectorsControler & p_sectors);

    AntennaLossForSectors calculate();
    void setReciver(PixelXY p_pixel);
private:
    void check(const Sector & sector, AntennaLossHorizontalCalculator & horizontalCalculator);
    void check(const Sector & sector, AntennaLossVerticalCalculator & verticalCalculator);

    float lossVertical(const Sector & sector);
    float lossHorizontal(const Sector & sector);

    std::shared_ptr<IMapDataProvider> mapDataProvider;
    SectorsControler & sectors;
    PixelXY pixel;
};

#endif // ANTENNALOSSCALCULATION_H
