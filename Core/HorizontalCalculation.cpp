#include "HorizontalCalculation.h"

HorizontalCalculation::HorizontalCalculation(AntennaLossHorizontalCalculator & p_calculator) :
    calculator(p_calculator)
{
}

void HorizontalCalculation::calculate(const Receiver receiver, const SectorsControler & sectors)
{
//    std::vector<Sector> newSectors;
//    calculator.setReceiver(receiver);
//    for(auto sector : sectors.getVectorOfSectors())
//    {
//        calculator.setAntenna(sector.getPossitonOfBaseStation());
//        calculator.calculateAzimuth();

//    }

}


