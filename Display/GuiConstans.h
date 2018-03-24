#ifndef GUICONSTANS_H
#define GUICONSTANS_H
#include <QString>
#include <map>

#define E_NB_ID           1
#define POSITION          2
#define HEIGHT            3
#define SECTOR_ID         4
#define POWER             5
#define BAND              6
#define BANDWIDTH         7
#define AZIMUT            8
#define MIMO              9
#define ENVIRNOMENT       10
#define PROPAGATION_MODEL 11
#define GAIN              12
#define TILT              13
#define FILE_H            14
#define FILE_V            15

#define SMALL_AND_MEDIUM_SIZE_CITIES 16
#define METROPOLITAN_AREAS           17
#define SUBURBAN_ENV                 18
#define RURAL_AREA                   19

namespace GUI
{
const QString eNbName = "eNBId";
const QString position = "Position";
const QString height = "Height [m n.p.t]";
const QString sectorIdx = "Sector";
const QString power = "Power [dB]";
const QString band = "Band [MHz]";
const QString bandwidth = "Bandwidth [MHz]";
const QString azimuth = "Azimuth [deegres]";
const QString mimo = "MIMO";
const QString environment = "Environment";
const QString propModel = "Propagation model";
const QString gain = "Gain [dBi]";
const QString tilt = "Tilt [deegres]";
const QString fileH = "Horizontal";
const QString fileV = "Vertical";

const QString sectors = "Sectors";
const QString antenna = "Antenna";
const QString charFiles = "Characteristics files";

const std::map<QString, int> behaviorMap = {
    {eNbName, E_NB_ID},
    {position, POSITION},
    {height, HEIGHT},
    {sectorIdx, SECTOR_ID},
    {power, POWER},
    {band, BAND},
    {bandwidth, BANDWIDTH},
    {azimuth, AZIMUT},
    {mimo, MIMO},
    {environment, ENVIRNOMENT},
    {propModel, PROPAGATION_MODEL},
    {gain, GAIN},
    {tilt, TILT},
    {fileV, FILE_V},
    {fileH, FILE_H}};
}

#endif // GUICONSTANS_H
