#pragma once
#include <vector>
#include <utility>

enum class Modulation
{
    unused,
    QPSK,
    QAM16,
    QAM64,
    QAM256
};

struct ModulationSchemeAndSnrMapping
{
    Modulation modulation;
    double codingRate;
    double minSnr;
    double maxSnr;
    int valencOfMod;
};

struct MCSIdxAndTBSIdxMapping
{
    int mcsIdx;
    int tbsIdx;
};

const std::vector<ModulationSchemeAndSnrMapping> modulationAndSnrMappingTable =
{
    {Modulation::unused,  0,        -30,     -6.7536, 0},
    {Modulation::QPSK,    0.0762,   -6.7536, -4.9620, 2},
    {Modulation::QPSK,    0.1885,   -4.9620, -2.9601, 2},
    {Modulation::QPSK,    0.4385,   -2.9601, -1.0135, 2},
    {Modulation::QAM16,   0.3691,   -1.0135, 0.9638, 4},
    {Modulation::QAM16,   0.4785,   0.9638,  2.8801, 4},
    {Modulation::QAM16,   0.6016,   2.8801,  4.9185, 4},
    {Modulation::QAM64,   0.4551,   4.9185,  6.7005, 6},
    {Modulation::QAM64,   0.5537,   6.7005,  8.7198, 6},
    {Modulation::QAM64,   0.6504,   8.7198,  10.515, 6},
    {Modulation::QAM64,   0.7539,   10.515,  12.450, 6},
    {Modulation::QAM64,   0.8525,   12.450,  14.348, 6},
    {Modulation::QAM256,  0.6943,   14.348,  16.074, 8},
    {Modulation::QAM256,  0.7783,   16.074,  17.877, 8},
    {Modulation::QAM256,  0.8634,   17.877,  19.968, 8},
    {Modulation::QAM256,  0.9258,   19.968,  40, 8},
};
