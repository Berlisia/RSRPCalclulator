#ifndef SECTOR_H
#define SECTOR_H
#include "Antenna.h"
#include "BaseStation.h"
#include <memory>
#include <string>

enum class MIMO
{
    Nan,
    TwoAntenna,
    FourAntenna
};

class Sector
{
public:
    Sector(Antenna & antenna, std::shared_ptr<BaseStation> baseStation);

    void setAzimuth(int newAzimuth);
    void setBandwidth(double newBandwith);
    void setMimo(MIMO newMimo);

    int getAzimuth();
    float getPower() const;
    int getFrequency() const;
    double getBandwith() const;
    float getAntennaHeight();
    int getAntennaTilt();
    std::pair<int,int> getPossitonOfBaseStation();
    std::string getBaseStationName();

private:
    int azimuth;      //stopnie
    double bandwidth; //MHz
    MIMO mimo;
    std::shared_ptr<Antenna> antenna;
    std::shared_ptr<BaseStation> baseStation;
};

#endif // SECTOR_H
