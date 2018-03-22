#ifndef MODELTYPES_H
#define MODELTYPES_H
#include <QString>

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

enum class Environment
{
    Idle,
    SmallAndMediumSizeCities,
    MetropolitanAreas,
    SuburbanEvironments,
    RuralAera
};
MIMO qStringtoMimo(QString p_qstring);
QString mimoToString(MIMO p_mimo);

#endif
