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

private:
    std::unique_ptr<AntennaLossFileParser> horizontal;
    std::unique_ptr<AntennaLossFileParser> vertical;
};

#endif // ANTENNALOSSFILEPROVIDER_H
