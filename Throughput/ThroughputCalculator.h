#pragma once
#include "DataProvider.h"

class ThroughputCalculator
{
public:
    ThroughputCalculator(Throughput& thrData);
    void calculate();
private:
    Throughput& thrData;
};
