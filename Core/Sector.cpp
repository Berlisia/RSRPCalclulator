#include "Sector.h"

Sector::Sector(Antenna & p_antenna, std::shared_ptr<BaseStation> baseStation) :
                azimuth(0),
                bandwidth(0),
                mimo(MIMO::Nan),
                baseStation(baseStation)
{
    antenna = std::make_shared<Antenna>(std::move(p_antenna));
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
    return antenna->getPower();
}

double Sector::getBandwith() const
{
    return bandwidth;
}

float Sector::getAntennaHeight()
{
    return baseStation->getAntennaHeight();
}

int Sector::getAntennaTilt()
{
    return antenna->getTilt();
}

std::pair<int, int> Sector::getPossitonOfBaseStation()
{
    return baseStation->getPossition();
}

