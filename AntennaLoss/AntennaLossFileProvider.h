#ifndef ANTENNALOSSFILEPROVIDER_H
#define ANTENNALOSSFILEPROVIDER_H
#include "IAntennaLossFileProvider.h"
#include "AntennaLossFileParser.h"
#include "memory"

class AntennaLossFileProvider : public IAntennaLossFileProvider
{
public:
    AntennaLossFileProvider(std::string horizontalFileName, std::string verticalFileName);
    float getLossFromFile(int angle, Charakteristic type) override;
    void changeFileHorizontal(QString path) override;
    void changeFileVertical(QString path) override;
    ~AntennaLossFileProvider(){}

private:
    std::unique_ptr<AntennaLossFileParser> horizontal;
    std::unique_ptr<AntennaLossFileParser> vertical;
};

#endif // ANTENNALOSSFILEPROVIDER_H
