#include "AntennaLossFileParser.h"
#include "iostream"
#include "algorithm"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <QString>
using namespace std;

const int AntennaLossFileParser::numberOfLine = 360;

AntennaLossFileParser::AntennaLossFileParser(string fileName) :
    fileName(fileName)
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

void AntennaLossFileParser::changefileName(string newFileName)
{
    fileName = newFileName;
}

void AntennaLossFileParser::getDataFromFile()
{
    fstream file;
    file.open(fileName, ios::in);
//    if(chmod(fileName.c_str(),0777) == -1)
//    {
//        if(access(fileName.c_str(), R_OK) == -1)
//        cout << "Nie masz praw" << endl;
//    }
    if(file.good())
    {
        string angle = "";
        string value = "";
        for(int i = 0; i < numberOfLine; i++)
        {
            getline(file, angle,';');
            getline(file, value);

            QString qvalue(value.c_str());
            int intAngle = stoi(angle);
            double doubleValue = qvalue.toDouble();

            auto pairFromFile = std::pair<int,double>(intAngle, doubleValue);
            array.push_back(pairFromFile);
        }
    }
    else
    {
        cout << "File Error" << endl;
    }
}

double AntennaLossFileParser::findLossformArray(int angle)
{
    auto loss = find_if(array.begin(), array.end(),
                        [angle](const pair<int, double>& element)
                        {
                            return element.first == angle;
                        });
    if (loss != array.end())
    {
        return loss->second;
    }
    return -1;
}

