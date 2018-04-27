#include "AntennaLossFileParserTest.h"
#include "AntennaLoss/AntennaLossFileParser.h"
#include "iostream"

AntennaLossFileParserTest::AntennaLossFileParserTest()
{
    std::string file = "742266V02_pozioma.csv";
    AntennaLossFileParser parser(file);
    int angle = 300;
    double dupa = parser.getLoss(angle);
    std::cout << "stopnie " << angle << ": " << dupa << std::endl;
}
