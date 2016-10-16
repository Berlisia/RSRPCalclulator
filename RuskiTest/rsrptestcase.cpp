#include "rsrptestcase.h"
#include "RSRP/IRsrpCalculation.h"
#include "RSRP/RsrpCalculation.h"
#include "RSRP/RsrpInitialization.h"

#include <memory>
#include <vector>
#include <iostream>
using namespace std;

void RsrpTestCase::rsrpCalculationTest()
{
    BaseStation base1;
    BaseStation base2;

    Antenna antenna(20,0,1800);
    Antenna antenna2(20,0,1800);
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

    vector<Sector*> sectors
    {
        &sec11, &sec21, &sec31, &sec12, &sec22, &sec32
    };

    RsrpInitialization rsrpInit;
    unique_ptr<IRsrpCalculation> calculator(new RsrpCalculation(rsrpInit));
    PixelPoint pixel(sectors);
    float maxValue = calculator->calculateRsrp(pixel);
    cout << "Max Value from rsrp vector: " << maxValue << endl;
}
