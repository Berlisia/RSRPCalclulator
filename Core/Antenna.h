#ifndef ANTENNA_H
#define ANTENNA_H
#include <functional>

class Antenna
{
public:
    Antenna(float power, int tilt, int frequency);
    void setPower(float newPower);
    void setTilt(int newTilt);
    void setFrequency(int newFrequency);

    float getPower();
    //std::pair<int,int> getPosition();

private:
    float power;
    int tilt;
    int frequency; //MHz
};

#endif // ANTENNA_H
