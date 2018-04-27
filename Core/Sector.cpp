#include "Sector.h"

Sector::Sector(Antenna & p_antenna, std::shared_ptr<BaseStation> p_baseStation) :
                azimuth(0),
                bandwidth(0),
                mimo(Mimo::Nan),
                baseStation(std::move(p_baseStation))
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

void Sector::setMimo(Mimo newMimo)
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

void Sector::setPower(double newPower)
{
    antenna->setPower(newPower);
}

void Sector::setBand(int newfrequency)
{
    antenna->setFrequency(newfrequency);
}

void Sector::setGain(double newGain)
{
    antenna->setGain(newGain);
}

void Sector::setTilt(int newTilit)
{
    antenna->setTilt(newTilit);
}

void Sector::setFileHName(QString newPath)
{
    antennaCharacteristic->changeFileHorizontal(std::move(newPath));
}

void Sector::setFileVName(QString newPath)
{
    antennaCharacteristic->changeFileVertical(std::move(newPath));
}

int Sector::getAzimuth() const
{
    return azimuth;
}

double Sector::getPower() const
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

int Sector::getBandIndex() const
{
    return antenna->getBandIndex();
}

double Sector::getAntennaHeight() const
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

Mimo Sector::getMimo() const
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

