#include "modeltypes.h"

MIMO qStringtoMimo(QString p_qstring)
{
    if(p_qstring == "2x2")
        return MIMO::TwoAntenna;
    else if(p_qstring == "4x4")
        return MIMO::FourAntenna;
    return MIMO::Nan;
}

QString mimoToString(MIMO p_mimo)
{
    if(p_mimo == MIMO::TwoAntenna)
        return "2x2";
    else if(p_mimo == MIMO::FourAntenna)
        return "4x4";
    return "Nan";
}
