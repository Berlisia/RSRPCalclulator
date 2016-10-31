#include "rsrptestcase.h"
#include "RSRP/IRsrpCalculation.h"
#include "RSRP/RsrpCalculation.h"
#include "RSRP/RsrpInitialization.h"
#include "Core/PixelControler.h"

#include <memory>
#include <vector>
#include <iostream>
using namespace std;

void RsrpTestCase::rsrpCalculationTest()
{
    BaseStation base1(std::make_pair<int,int>(1500,1500), 120.0);
    BaseStation base2(std::make_pair<int,int>(1800,1800), 130.0);

    std::vector<std::pair<int,int>> area;

    area.push_back(std::make_pair<int,int>(1000,1000));
    area.push_back(std::make_pair<int,int>(2000,1000));
    area.push_back(std::make_pair<int,int>(1000,2000));
    area.push_back(std::make_pair<int,int>(2000,2000));

    AreaCalculation areaCalc(area);

    Antenna antenna(20,0,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");
    Antenna antenna2(20,0,1800, "742266V02_pozioma.csv","742266V02_pionowa.csv");
    Sector sec11(antenna, base1);
    Sector sec21(antenna, base1);
    Sector sec31(antenna, base1);

    Sector sec12(antenna2, base2);
    Sector sec22(antenna2, base2);
    Sector sec32(antenna2, base2);

    sec11.setBandwidth(10.0);
    sec21.setBandwidth(15.0);
    sec31.setBandwidth(20.0);

    sec12.setBandwidth(10.0);
    sec22.setBandwidth(15.0);
    sec32.setBandwidth(20.0);

    vector<Sector> sectors
    {
        sec11, sec21, sec31, sec12, sec22, sec32
    };
    SectorsControler sectorControler(sectors);

    RsrpInitialization rsrpInit;
    unique_ptr<IRsrpCalculation> calculator(new RsrpCalculation(rsrpInit));
    std::vector<float> rsrpFromSectors;
    for(auto sec : sectors)
    {
        rsrpFromSectors.push_back(calculator->calculateRsrp(sec));
    }
    float maxValue = calculator->findMaxRsrpFromSectors(rsrpFromSectors);
    cout << "Max Value from rsrp vector: " << maxValue << endl;
}
