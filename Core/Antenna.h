#ifndef ANTENNA_H
#define ANTENNA_H
#include <functional>

class Antenna
{
public:
    Antenna(float power, double gain, int tilt, int frequency, std::string horizonral, std::string vertical);
    void setPower(float newPower);
    void setTilt(int newTilt);
    void setFrequency(int newFrequency);

    float getPower();
    int getTilt();
    int getFrequency();
    std::string getFileNameH();
    std::string getFileNameV();
    double getGain() const;
    void setGain(double value);

private:

    float power;
    double gain;
    int tilt;
    int frequency; //MHz
    std::string fileNameH;
    std::string fileNameV;
};

#endif // ANTENNA_H
