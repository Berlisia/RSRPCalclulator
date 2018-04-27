#ifndef ANTENNALOSSFILEPARSER_H
#define ANTENNALOSSFILEPARSER_H
#include "vector"
#include "utility"
#include "string"
#include "fstream"

typedef std::vector<std::pair<int,double>> ArrayOfAntennaLoss;

class AntennaLossFileParser
{
public:
    AntennaLossFileParser(std::string fileName);
    double getLoss(int angle);
    void changefileName(std::string newfileName);

private:
    void getDataFromFile();
    double findLossformArray(int angle);

    std::string fileName;
    ArrayOfAntennaLoss array;

    static const int numberOfLine = 360;
};

#endif // ANTENNALOSSFILEPARSER_H
