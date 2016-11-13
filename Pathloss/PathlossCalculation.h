#ifndef PATHLOSSCALCULATION_H
#define PATHLOSSCALCULATION_H
#include "IPathlossCalculation.h"
#include "MapProvider/IMapDataProvider.h"
#include "Core/SectorsControler.h"
#include "Core/Receiver.h"
#include <memory>
class PathlossCalculation : public IPathlossCalculation
{
public:
    PathlossCalculation(std::shared_ptr<IMapDataProvider> p_mapProvider,
                        SectorsControler & p_sectors,
                        Receiver & p_receiver);

    std::vector<float> calculatePathloss(); //Wybierz model
    float effectiveBAntennaHeight(Sector & sector);
    ~PathlossCalculation(){}

private:
    void setUpParameters(PathlossModel & model, Sector & sector);
    std::shared_ptr<IMapDataProvider> mapProvider;
    SectorsControler & sectors;
    Receiver & receiver;

};

#endif // PATHLOSSCALCULATION_H
