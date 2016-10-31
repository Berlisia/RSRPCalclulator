#ifndef ANTENNALOSSCALCULATION_H
#define ANTENNALOSSCALCULATION_H
#include "AntennaLossHorizontalCalculator.h"
#include "AntennaLossVerticalCalculator.h"
#include "Core/SectorsControler.h"

#include <memory>

typedef std::shared_ptr<std::vector<float>> AntennaLossForSectors;

//struct Parameters
//{
//   std::pair<int,int> baseStationPossition;
//   float baseStationHeight;
//   std::pair<int,int> receiverPossition;
//};

class AntennaLossCalculation
{
public:
    AntennaLossCalculation(std::shared_ptr<IMapDataProvider> p_mapDataProvider,
                           std::shared_ptr<IAntennaLossFileProvider> p_antennaLossDataProvider,
                           SectorsControler & p_sectors);

//    void setParam(std::pair<int,int> p_baseStationPossition,
//                  float p_baseStationHeight,
//                  std::pair<int,int> p_receiverPossition);

    AntennaLossForSectors calculate();
private:
    void check(Sector & sector);

    std::shared_ptr<IMapDataProvider> mapDataProvider;
    std::shared_ptr<IAntennaLossFileProvider> antennaLossDataProvider;
    SectorsControler & sectors;

    std::shared_ptr<AntennaLossHorizontalCalculator> horizontalCalculator;
    std::shared_ptr<AntennaLossVerticalCalculator> verticalCalculator;

    //Parameters param;
};

#endif // ANTENNALOSSCALCULATION_H
