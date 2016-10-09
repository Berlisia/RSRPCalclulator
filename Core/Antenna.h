#ifndef ANTENNA_H
#define ANTENNA_H


class Antenna
{
public:
    Antenna(float power, int tilt, int frequency);
    void setPower(float newPower);
    void setTilt(int newTilt);
    void setFrequency(int newFrequency);

    float getPower();

private:
    float power;
    int tilt;
    int frequency; //MHz
};

#endif // ANTENNA_H
