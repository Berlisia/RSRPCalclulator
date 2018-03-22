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

void Sector::setEnvironment(Environment newEnv)
{
    environment = newEnv;
}

void Sector::setModel(Model newModel)
{
    model = newModel;
}

void Sector::setEcgi(int newEcgi)
{
    ecgi = newEcgi;
}

int Sector::getAzimuth() const
{
    return azimuth;
}

float Sector::getPower() const
{
    return antenna->getPower();
}

int Sector::getFrequency() const
{
    return antenna->getFrequency();
}

double Sector::getBandwith() const
{
    return bandwidth;
}

float Sector::getAntennaHeight() const
{
    return baseStation->getAntennaHeight();
}

int Sector::getAntennaTilt() const
{
    return antenna->getTilt();
}

Environment Sector::getEnvironment() const
{
    return environment;
}

MIMO Sector::getMimo() const
{
    return mimo;
}

Model Sector::getModel() const
{
    return model;
}

std::pair<int, int> Sector::getPossitonOfBaseStation() const
{
    return baseStation->getPossition();
}

std::string Sector::getBaseStationName() const
{
    return baseStation->getName();
}

double Sector::getGain() const
{
    return antenna->getGain();
}

std::shared_ptr<IAntennaLossFileProvider> Sector::getAntennaCharacteristic() const
{
    return antennaCharacteristic;
}

void Sector::setAntennaCharacteristic(const std::shared_ptr<IAntennaLossFileProvider> &value)
{
    antennaCharacteristic = value;
}

std::string Sector::getVerticalFileName() const
{
    return antenna->getFileNameV();
}

std::string Sector::getHorizontalFileName() const
{
    return antenna->getFileNameH();
}

int Sector::getEcgi() const
{
    return ecgi;
}

