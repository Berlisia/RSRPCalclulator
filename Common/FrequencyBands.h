#pragma once
#include <utility>
#include <vector>

const double numberOfSubcarriersInRB = 12.0;
const double subcarrierActivityFactor = 5./3.;

enum Duplex
{
    FDD,
    TDD
};

struct FreqBand
{
    int bw;
    Duplex duplex;
    std::pair<int,int> ulFreq;
    std::pair<int,int> dlFreq;
};

const std::vector<FreqBand> freqBandList = {
            {FreqBand{1,Duplex::FDD,std::make_pair(1920,1980),std::make_pair(2110,2170)}},
            {FreqBand{3,Duplex::FDD,std::make_pair(1710,1785),std::make_pair(1805,1880)}},
            {FreqBand{7,Duplex::FDD,std::make_pair(2500,2570),std::make_pair(2620,2690)}},
            {FreqBand{8,Duplex::FDD,std::make_pair(880,915),std::make_pair(925,960)}},
            {FreqBand{20,Duplex::FDD,std::make_pair(832,862),std::make_pair(791,821)}},
            {FreqBand{38,Duplex::TDD,std::make_pair(2570,2620),std::make_pair(2570,2620)}}};
