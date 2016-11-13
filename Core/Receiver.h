#ifndef RECEIVER_H
#define RECEIVER_H
#include "PixelXY.h"

class Receiver
{
public:
    Receiver();
    PixelXY getPossition();
    float getHeight();

    void setPossition(std::pair<int,int> p_possition);
    void setHeight(float value);
private:
    PixelXY possition;
    float height;
};

#endif // RECEIVER_H
