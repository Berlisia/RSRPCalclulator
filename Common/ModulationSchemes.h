#pragma once
#include <vector>
#include <utility>

enum class Modulation
{
    failure,
    QPSK,
    QAM16,
    QAM64
};

struct ModulationSchemeAndSnrMapping
{
    Modulation modulation;
    double codingRate;
    double minSnr;
    double maxSnr;
};

const std::vector<ModulationSchemeAndSnrMapping> modulationAndSnrMappingTable =
{
    {Modulation::failure, 0,            -30, -6.7536},
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
};
