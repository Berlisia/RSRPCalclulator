#ifndef MODELTYPES_H
#define MODELTYPES_H
#include <QString>

enum class Mimo
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
Mimo qStringtoMimo(const QString& p_qstring);
QString mimoToString(Mimo p_mimo);
Model qStringToPropragationModel(const QString& p_qString);
QString propagationModelToString(Model p_propModel);
Environment qStringToEnvironment(const QString& p_qString);
QString environmentToString(Environment p_env);
Environment converQEnvironment(int index);

#endif
