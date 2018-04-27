#include "AntennaLossFileParser.h"
#include "iostream"
#include "algorithm"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <QString>

AntennaLossFileParser::AntennaLossFileParser(std::string fileName) :
    fileName(std::move(fileName))
{
    getDataFromFile();
}

double AntennaLossFileParser::getLoss(int angle)
{
    if (angle < numberOfLine)
    {
        double loss = findLossformArray(angle);
        return loss;
    }
    return -1;
}

void AntennaLossFileParser::changefileName(std::string newfileName)
{
    fileName = std::move(newfileName);
}

void AntennaLossFileParser::getDataFromFile()
{
    std::fstream file;
    file.open(fileName, std::ios::in);
//    if(chmod(fileName.c_str(),0777) == -1)
//    {
//        if(access(fileName.c_str(), R_OK) == -1)
//        cout << "Nie masz praw" << endl;
//    }
    if(file.good())
    {
        std::string angle;
        std::string value;
        for(int i = 0; i < numberOfLine; i++)
        {
            std::getline(file, angle,';');
            std::getline(file, value);

            QString qvalue(value.c_str());
            int intAngle = stoi(angle);
            double doubleValue = qvalue.toDouble();

            auto pairFromFile = std::pair<int,double>(intAngle, doubleValue);
            array.push_back(pairFromFile);
        }
    }
    else
    {
        std::cout << "File Error" << std::endl;
    }
}

double AntennaLossFileParser::findLossformArray(int angle)
{
    auto loss = find_if(array.begin(), array.end(),
                        [angle](const std::pair<int, double>& element)
                        {
                            return element.first == angle;
                        });
    if (loss != array.end())
    {
        return loss->second;
    }
    return -1;
}

