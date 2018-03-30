#include "Antenna.h"
#include "Common/FrequencyBands.h"
#include <algorithm>

Antenna::Antenna(double power, double gain, int tilt, int bandBw, std::string fileH, std::string fileV) :
    power(power),
    gain(gain),
    tilt(tilt),
    fileNameH(fileH),
    fileNameV(fileV)
{
    setBandByIndex(bandBw);
    frequency = (band.dlFreq.second - band.dlFreq.first) / 2;
}

void Antenna::setPower(double newPower)
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

double Antenna::getPower()
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

int Antenna::getBandIndex() const
{
    return band.bw;
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

const FreqBand& Antenna::getFreqBand()
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
    auto bandIter = std::find_if(freqBandList.begin(), freqBandList.end(),
                             [bw](FreqBand bwList) -> bool {return bwList.bw == bw;});
    band.bw = bandIter->bw;
    band.dlFreq = bandIter->dlFreq;
    band.ulFreq = bandIter->ulFreq;
    band.duplex = bandIter->duplex;
}

