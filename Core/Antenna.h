#ifndef ANTENNA_H
#define ANTENNA_H
#include <functional>

class Antenna
{
public:
    Antenna(float power, int tilt, int frequency, std::string horizonral, std::string vertical);
    void setPower(float newPower);
    void setTilt(int newTilt);
    void setFrequency(int newFrequency);

    float getPower();
    int getTilt();
    std::pair<int,int> getPosition();
    std::string getFileNameH();
    std::string getFileNameV();

private:

    float power;
    int tilt;
    int frequency; //MHz
    std::pair<int,int> position;
    std::string fileNameH;
    std::string fileNameV;
};

#endif // ANTENNA_H
