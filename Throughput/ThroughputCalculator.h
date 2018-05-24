#pragma once
#include "DataProvider.h"

class ThroughputCalculator
{
public:
    ThroughputCalculator(const Throughput& thrData);
    void calculate();
private:
    const Throughput& thrData;
};
