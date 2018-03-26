#ifndef ANTENNA_H
#define ANTENNA_H
#include <functional>
#include "Common/FrequencyBands.h"

class Antenna
{
public:
    Antenna(float power, double gain, int tilt, int frequency, std::string horizonral, std::string vertical);

    void setPower(float newPower);
    void setTilt(int newTilt);
    void setFrequency(int newFrequency);
    void setBand(FreqBand newBand);
    void setBandByIndex(int bw);

    float getPower();
    int getTilt();
    int getFrequency();
    std::string getFileNameH();
    std::string getFileNameV();
    double getGain() const;
    void setGain(double value);

    FreqBand getFreqBand();

private:
    float power;
    double gain;
    int tilt;
    int frequency; //MHz
    FreqBand band;
    std::string fileNameH;
    std::string fileNameV;
};

#endif // ANTENNA_H
