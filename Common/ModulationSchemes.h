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
};

struct MCSIdxAndTBSIdxMapping
{
    int mcsIdx;
    int tbsIdx;
};

const std::vector<ModulationSchemeAndSnrMapping> modulationAndSnrMappingTable =
{
    {Modulation::unused,  0,        -30,     -6.7536},
    {Modulation::QPSK,    0.0762,   -6.7536, -4.9620},
    {Modulation::QPSK,    0.1885,   -4.9620, -2.9601},
    {Modulation::QPSK,    0.4385,   -2.9601, -1.0135},
    {Modulation::QAM16,   0.3691,   -1.0135, 0.9638},
    {Modulation::QAM16,   0.4785,   0.9638,  2.8801},
    {Modulation::QAM16,   0.6016,   2.8801,  4.9185},
    {Modulation::QAM64,   0.4551,   4.9185,  20.7005},
    {Modulation::QAM64,   0.5537,   20.7005, 25.7198},
    {Modulation::QAM64,   0.6504,   25.7198, 30.515},
    {Modulation::QAM64,   0.7539,   30.515,  35.450},
    {Modulation::QAM64,   0.8525,   35.450,  40.348},
    {Modulation::QAM256,  0.6943,   40.348,  45.074},
    {Modulation::QAM256,  0.7783,   45.074,  47.877},
    {Modulation::QAM256,  0.8634,   47.877,  49.968},
    {Modulation::QAM256,  0.9258,   59.968,  60},
};

/*
 *     {Modulation::failure, 0,            -30, -6.7536},
    {Modulation::QPSK,    0.076171875,  -6.7536, -4.9620},
    {Modulation::QPSK,    0.1171875,    -4.9620, -2.9601},
    {Modulation::QPSK,    0.1884765625, -2.9601, -1.0135},
    {Modulation::QPSK,    0.30078125,   -1.0135, 0.9638},
    {Modulation::QPSK,    0.4384765625, 0.9638,  2.8801},
    {Modulation::QPSK,    0.587890625,  2.8801,  4.9185},
    {Modulation::QAM16,   0.369140625,  4.9185,  6.7005},
    {Modulation::QAM16,   0.478515625,  6.7005,  8.7198},
    {Modulation::QAM16,   0.599609375,  8.7198,  10.515},
    {Modulation::QAM64,   0.455078125,  10.515,  12.450},
    {Modulation::QAM64,   0.5537109375, 12.450,  14.348},
    {Modulation::QAM64,   0.650390625,  14.348,  16.074},
    {Modulation::QAM64,   0.75390625,   16.074,  17.877},
    {Modulation::QAM64,   0.8525390625, 17.877,  19.968},
    {Modulation::QAM64,   0.92578125,   19.968,  40},
    */
