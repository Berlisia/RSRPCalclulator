#ifndef HORIZONTALCALCULATION_H
#define HORIZONTALCALCULATION_H
#include "AntennaLoss/AntennaLossHorizontalCalculator.h"
#include "SectorsControler.h"
#include "Receiver.h"


class HorizontalCalculation
{
public:
    HorizontalCalculation(AntennaLossHorizontalCalculator & p_calculator);

    void calculate(const Receiver receiver, const SectorsControler & sectors);

private:
    AntennaLossHorizontalCalculator & calculator;
};

#endif // HORIZONTALCALCULATION_H
