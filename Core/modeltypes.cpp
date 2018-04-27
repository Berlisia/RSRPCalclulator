#include "modeltypes.h"
#include "Display/GuiConstans.h"

Mimo qStringtoMimo(const QString& p_qstring)
{
    if (p_qstring == "2x2")
    {
        return Mimo::TwoAntenna;
    }
    else if (p_qstring == "4x4")
    {
        return Mimo::FourAntenna;
    }
    return Mimo::Nan;
}

QString mimoToString(Mimo p_mimo)
{
    if (p_mimo == Mimo::TwoAntenna)
    {
        return "2x2";
    }
    else if (p_mimo == Mimo::FourAntenna)
    {
        return "4x4";
    }
    return "Nan";
}

Model qStringToPropragationModel(const QString& p_qString)
{
    if (p_qString == "Okumura Hata")
    {
        return Model::OkumuraHata;
    }
    return Model::Cost231Hata;
}

QString propagationModelToString(Model p_propModel)
{
    if (p_propModel == Model::OkumuraHata)
    {
        return "Okumura Hata";
    }
    return "Cost 231 Hata";
}

Environment qStringToEnvironment(const QString& p_qString)
{
    if (p_qString == "Small And Medium Size Cities")
    {
        return Environment::SmallAndMediumSizeCities;
    }
    else if (p_qString == "Metropolitan Areas")
    {
        return Environment::MetropolitanAreas;
    }
    else if (p_qString == "Suburban Evironments")
    {
        return Environment::SuburbanEvironments;
    }
    else if (p_qString == "Rural Aera")
    {
        return Environment::RuralAera;
    }
    return Environment::Idle;
}

QString environmentToString(Environment p_env)
{
    if (p_env == Environment::SmallAndMediumSizeCities)
    {
        return "Small And Medium Size Cities";
    }
    else if (p_env == Environment::MetropolitanAreas)
    {
        return "Metropolitan Areas";
    }
    else if (p_env == Environment::SuburbanEvironments)
    {
        return "Suburban Evironments";
    }
    else if (p_env == Environment::RuralAera)
    {
        return "Rural Aera";
    }
    return "-";
}

Environment converQEnvironment(int index)
{
    switch (index)
    {
        case SMALL_AND_MEDIUM_SIZE_CITIES:
            return Environment::SmallAndMediumSizeCities;
        case METROPOLITAN_AREAS:
            return Environment::MetropolitanAreas;
        case SUBURBAN_ENV:
            return Environment::SuburbanEvironments;
        case RURAL_AREA:
            return Environment::RuralAera;
        default:
            return Environment::Idle;
    }
}
