#include "AntennaLossFileParserTest.h"
#include "AntennaLoss/AntennaLossFileParser.h"
#include "iostream"
using namespace std;

AntennaLossFileParserTest::AntennaLossFileParserTest()
{
    std::string file = "742266V02_pozioma.csv";
    AntennaLossFileParser parser(file);
    int angle = 300;
    float dupa = parser.getLoss(angle);
    cout << "stopnie " << angle << ": " << dupa << endl;
}
