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
Model qStringToPropragationModel(QString p_qString);
QString propagationModelToString(Model p_propModel);
Environment qStringToEnvironment(QString p_qString);
QString environmentToString(Environment p_env);


#endif
