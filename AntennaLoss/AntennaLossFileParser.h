#ifndef ANTENNALOSSFILEPARSER_H
#define ANTENNALOSSFILEPARSER_H
#include "vector"
#include "utility"
#include "string"
#include "fstream"

typedef std::vector<std::pair<int,float>> ArrayOfAntennaLoss;

class AntennaLossFileParser
{
public:
    AntennaLossFileParser(std::string fileName);
    float getLoss(int angle);

private:
    void getDataFromFile();
    float findLossformArray(int angle);

    std::string fileName;
    ArrayOfAntennaLoss array;

    static const int numberOfLine;
};

#endif // ANTENNALOSSFILEPARSER_H
