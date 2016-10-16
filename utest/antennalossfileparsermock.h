#ifndef ANTENNALOSSFILEPARSERMOCK_H
#define ANTENNALOSSFILEPARSERMOCK_H
#include "AntennaLoss/AntennaLossFileParser.h"
#include <gmock/gmock.h>

class AntennaLossFileParserMock : public AntennaLossFileParser
{
public:
    AntennaLossFileParserMock(std::string fileName) :
        AntennaLossFileParser(fileName)
    {}

    MOCK_METHOD1(getLoss, float(int));
};

#endif //ANTENNALOSSFILEPARSER_H
