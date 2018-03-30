#include "SectorsControler.h"
#include "Display/GuiConstans.h"
#include <QDebug>

SectorsControler::SectorsControler(std::vector<Sector> & p_sector)
{
    sector = std::move(p_sector);
}

double SectorsControler::getPowerFromSector(int indexOfSector)
{
    return sector[indexOfSector].getPower();
}

double SectorsControler::getBandwithFromSector(int indexOfSector)
{
    return sector[indexOfSector].getBandwith();
}

const std::vector<Sector>& SectorsControler::getVectorOfSectors()
{
    return sector;
}

int SectorsControler::getSectorECGI(int indexOfSector) const
{
    return sector[indexOfSector].getEcgi();
}

int SectorsControler::getBandIndexFromSector(int sectorIdx) const
{
    return sector[sectorIdx].getBandIndex();
}

//void SectorsControler::addSector(Antenna &antenna, BaseStation &base)
//{
//    sector->push_back(Sector(antenna,base));
//}

void SectorsControler::addSector(Sector p_sector)
{
    sector.push_back(p_sector);
}

void SectorsControler::modify(const int ecgi, const QString p_field, const QString p_value)
{
    auto findedSector = std::find_if(sector.begin(), sector.end(),
                               [ecgi](Sector p_sector) -> bool {return p_sector.getEcgi() == ecgi;});

    auto fieldType = GUI::behaviorMap.find(p_field)->second;
    switch (fieldType)
    {
    case SECTOR_ID:
        findedSector->setEcgi(p_value.toInt());
        break;
    case POWER:
        findedSector->setPower(p_value.toDouble());
        break;
    case BAND:
        findedSector->setBand(p_value.toInt());
        break;
    case BANDWIDTH:
        findedSector->setBandwidth(p_value.toDouble());
        break;
    case MIMO:
        findedSector->setMimo(qStringtoMimo(p_value));
        break;
    case ENVIRNOMENT:
        findedSector->setEnvironment(qStringToEnvironment(p_value));
        break;
    case PROPAGATION_MODEL:
        findedSector->setModel(qStringToPropragationModel(p_value));
        break;
    case GAIN:
        findedSector->setGain(p_value.toDouble());
        break;
    case TILT:
        findedSector->setTilt(p_value.toInt());
        break;
    case AZIMUT:
        findedSector->setAzimuth(p_value.toInt());
        break;
    case FILE_V:
        findedSector->setFileVName(p_value);
        break;
    case FILE_H:
        findedSector->setFileHName(p_value);
        break;
    default:
        qDebug() << "Something was wrong";
    }

}
