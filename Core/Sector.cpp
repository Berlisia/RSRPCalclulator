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

float Sector::getPower()
{
    return antenna.getPower();
}

double Sector::getBandwith()
{
    return bandwidth;
}

