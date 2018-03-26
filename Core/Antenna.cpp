#include "Antenna.h"

Antenna::Antenna(float power, double gain, int tilt, int frequency, std::string fileH, std::string fileV) :
    power(power),
    gain(gain),
    tilt(tilt),
    frequency(frequency),
    fileNameH(fileH),
    fileNameV(fileV)
{
}

void Antenna::setPower(float newPower)
{
    power = newPower;
}

void Antenna::setTilt(int newTilt)
{
    tilt = newTilt;
}

void Antenna::setFrequency(int newFrequency)
{
    frequency = newFrequency;
}

float Antenna::getPower()
{
    return power;
}

int Antenna::getTilt()
{
    return tilt;
}

int Antenna::getFrequency()
{
    return frequency;
}

std::string Antenna::getFileNameH()
{
    return fileNameH;
}

std::string Antenna::getFileNameV()
{
    return fileNameV;
}

double Antenna::getGain() const
{
    return gain;
}

void Antenna::setGain(double value)
{
    gain = value;
}

FreqBand Antenna::getFreqBand()
{
    return band;
}

void Antenna::setBand(FreqBand newBand)
{
    band.bw = newBand.bw;
    band.dlFreq = newBand.dlFreq;
    band.ulFreq = newBand.ulFreq;
    band.duplex = newBand.duplex;
}

void Antenna::setBandByIndex(int bw)
{

}

