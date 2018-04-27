#ifndef SECTOR_H
#define SECTOR_H
#include "Antenna.h"
#include "BaseStation.h"
#include "Pathloss/PathlossModel.h"
#include "AntennaLoss/IAntennaLossFileProvider.h"

#include <memory>
#include <string>

class Sector
{
public:
    Sector(Antenna & p_antenna, std::shared_ptr<BaseStation> p_baseStation);

    void setAzimuth(int newAzimuth);
    void setBandwidth(double newBandwith);
    void setMimo(Mimo newMimo);
    void setEnvironment(Environment newEnv);
    void setModel(Model newModel);
    void setEcgi(int newEcgi);

    void setPower(double newPower);
    void setBand(int newfrequency);
    void setGain(double newGain);
    void setTilt(int newTilit);
    void setFileHName(QString newPath);
    void setFileVName(QString newPath);

    int getAzimuth() const;
    double getPower() const;
    int getFrequency() const;
    double getBandwith() const;
    int getBandIndex() const;
    double getAntennaHeight() const;
    int getAntennaTilt() const;
    Environment getEnvironment() const;
    Mimo getMimo() const;
    Model getModel() const;
    std::pair<int, int> getPossitonOfBaseStation() const;
    std::string getBaseStationName() const;
    double getGain() const;
    std::shared_ptr<IAntennaLossFileProvider> getAntennaCharacteristic() const;
    void setAntennaCharacteristic(const std::shared_ptr<IAntennaLossFileProvider> &value);
    std::string getVerticalFileName() const;
    std::string getHorizontalFileName() const;
    int getEcgi() const;

private:
    int azimuth;      //stopnie
    double bandwidth; //MHz
    Mimo mimo;
    Environment environment;
    Model model;
    int ecgi;
    std::shared_ptr<Antenna> antenna;
    std::shared_ptr<BaseStation> baseStation;
    std::shared_ptr<IAntennaLossFileProvider> antennaCharacteristic;
};

#endif // SECTOR_H
