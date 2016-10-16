#include "AntennaLossFileParser.h"
#include "iostream"
#include "algorithm"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

const int AntennaLossFileParser::numberOfLine = 360;

AntennaLossFileParser::AntennaLossFileParser(std::string fileName) :
    fileName(fileName)
{
    getDataFromFile();
}

float AntennaLossFileParser::getLoss(int angle)
{
    if (angle < numberOfLine)
    {
        float loss = findLossformArray(angle);
        return loss;
    }
    return -1;
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
            int intAngle = stoi(angle);
            float floatValue = stof(value);

            auto pairFromFile = make_pair(intAngle, floatValue);
            array.push_back(pairFromFile);
        }
    }
    else
    {
        cout << "File Error" << endl;
    }
}

float AntennaLossFileParser::findLossformArray(int angle)
{
    auto loss = find_if(array.begin(), array.end(),
                        [angle](const pair<int, float>& element)
                        {
                            return element.first == angle;
                        });
    if (loss != array.end())
    {
        return loss->second;
    }
    return -1;
}

