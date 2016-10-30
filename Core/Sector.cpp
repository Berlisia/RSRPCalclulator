#include "Sector.h"

Sector::Sector(Antenna & antenna, BaseStation & baseStation) :
                azimuth(0),
                bandwidth(0),
                mimo(MIMO::Nan),
                antenna(antenna),
                baseStation(baseStation)
{
}

void Sector::setAzimuth(int newAzimuth)
{
    azimuth = newAzimuth;
}

void Sector::setBandwidth(double newBandwith)
{
    bandwidth = newBandwith;
}

void Sector::setMimo(MIMO newMimo)
{
    mimo = newMimo;
}

int Sector::getAzimuth()
{
    return azimuth;
}

float Sector::getPower() const
{
    return antenna.getPower();
}

double Sector::getBandwith() const
{
    return bandwidth;
}

float Sector::getAntennaHeight()
{
    return baseStation.getAntennaHeight();
}

int Sector::getAntennaTilt()
{
    return antenna.getTilt();
}

std::pair<int, int> Sector::getPossitonOfBaseStation()
{
    return baseStation.getPossition();
}

