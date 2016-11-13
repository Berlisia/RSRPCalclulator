#include "AntennaLossFileProvider.h"


AntennaLossFileProvider::AntennaLossFileProvider(std::string horizontalFileName, std::string verticalFileName) :
    horizontal(std::make_unique<AntennaLossFileParser>(horizontalFileName)),
    vertical(std::make_unique<AntennaLossFileParser>(verticalFileName))
{
}

float AntennaLossFileProvider::getLossFromFile(int angle, Charakteristic type)
{
    float loss = -1;
    if(type == Charakteristic::horizontal)
    {
        loss = horizontal->getLoss(angle);
    }
    else if (type == Charakteristic::vertical)
    {
        loss = vertical->getLoss(angle);
    }
    return loss;
}


