#ifndef SECTOR_H
#define SECTOR_H
#include "Antenna.h"
#include "BaseStation.h"
#include "Pathloss/PathlossModel.h"
#include "AntennaLoss/IAntennaLossFileProvider.h"

#include <memory>
#include <string>

enum class MIMO
{
    Nan,
    TwoAntenna,
    FourAntenna
};

enum class Model
{
    OkumuraHata,
    Cost231Hata
};

class Sector
{
public:
    Sector(Antenna & antenna, std::shared_ptr<BaseStation> baseStation);

    void setAzimuth(int newAzimuth);
    void setBandwidth(double newBandwith);
    void setMimo(MIMO newMimo);
    void setEnvironment(Environment newEnv);
    void setModel(Model newModel);
    void setEcgi(int newEcgi);

    int getAzimuth() const;
    float getPower() const;
    int getFrequency() const;
    double getBandwith() const;
    float getAntennaHeight() const;
    int getAntennaTilt() const;
    Environment getEnvironment() const;
    MIMO getMimo() const;
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
    MIMO mimo;
    Environment environment;
    Model model;
    int ecgi;
    std::shared_ptr<Antenna> antenna;
    std::shared_ptr<BaseStation> baseStation;
    std::shared_ptr<IAntennaLossFileProvider> antennaCharacteristic;
};

#endif // SECTOR_H
