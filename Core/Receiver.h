#ifndef RECEIVER_H
#define RECEIVER_H
#include "PixelXY.h"

class Receiver
{
public:
    Receiver(std::pair<int,int> p_possition);
    PixelXY getPossition();
    void setPossition(std::pair<int,int> p_possition);
private:
    PixelXY possition;
};

#endif // RECEIVER_H
