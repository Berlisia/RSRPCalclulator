#include "AntennaLossFileProvider.h"


AntennaLossFileProvider::AntennaLossFileProvider(std::string horizontalFileName, std::string verticalFileName) :
    horizontal(std::make_unique<AntennaLossFileParser>(horizontalFileName)),
    vertical(std::make_unique<AntennaLossFileParser>(verticalFileName))
{
}

double AntennaLossFileProvider::getLossFromFile(int angle, Charakteristic type)
{
    double loss = -1;
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

void AntennaLossFileProvider::changeFileHorizontal(QString path)
{
    horizontal->changefileName(path.toStdString());
}

void AntennaLossFileProvider::changeFileVertical(QString path)
{
    vertical->changefileName(path.toStdString());
}


