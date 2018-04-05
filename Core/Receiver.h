#ifndef RECEIVER_H
#define RECEIVER_H
#include "PixelXY.h"
#include <mutex>

class Receiver
{
public:
    Receiver();
    PixelXY getPossition() const;
    double getHeight() const;

    void setPossition(std::pair<int,int> p_possition);
    void setHeight(double value);
    double getGain() const;
    void setGain(double value);
    double getOtherLosses() const;
    void setOtherLosses(double value);

private:
    PixelXY possition;
    double height;
    double gain;
    double otherLosses;
};

#endif // RECEIVER_H
