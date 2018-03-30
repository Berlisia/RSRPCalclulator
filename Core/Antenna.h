#ifndef ANTENNA_H
#define ANTENNA_H
#include <functional>
#include "Common/FrequencyBands.h"

class Antenna
{
public:
    Antenna(double power, double gain, int tilt, int band, std::string horizonral, std::string vertical);

    void setPower(double newPower);
    void setTilt(int newTilt);
    void setFrequency(int newFrequency);
    void setBand(FreqBand newBand);
    void setBandByIndex(int bw);

    double getPower();
    int getTilt();
    int getFrequency();
    int getBandIndex() const;
    std::string getFileNameH();
    std::string getFileNameV();
    double getGain() const;
    void setGain(double value);

    const FreqBand& getFreqBand();

private:
    double power;
    double gain;
    int tilt;
    int frequency; //MHz
    FreqBand band;
    std::string fileNameH;
    std::string fileNameV;
};

#endif // ANTENNA_H
