#ifndef SECTOR_H
#define SECTOR_H
#include "Antenna.h"
#include "BaseStation.h"

enum class MIMO
{
    Nan,
    TwoAntenna,
    FourAntenna
};

class Sector
{
public:
    Sector(Antenna & antenna, BaseStation & baseStation);

    void setAzimuth(int newAzimuth);
    void setBandwidth(double newBandwith);
    void setMimo(MIMO newMimo);

    int getAzimuth();
    float getPower();
    double getBandwith();
    float getAntennaHeight();
    int getAntennaTilt();
    std::pair<int,int> getPossitonOfBaseStation();

private:
    int azimuth;      //stopnie
    double bandwidth; //MHz
    MIMO mimo;
    Antenna & antenna;
    BaseStation & baseStation;
};

#endif // SECTOR_H
