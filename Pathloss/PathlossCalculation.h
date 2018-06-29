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
                        SectorsControler& p_sectors,
                        const Receiver& p_receiver);

    std::vector<double> calculatePathloss(); //Wybierz model
    double effectiveBAntennaHeight(Sector const& sector);
    ~PathlossCalculation(){}

private:
    void setUpParameters(PathlossModel & model, Sector const& sector);
    Model choosePropagarionModel(const Sector &sector);
    Pathloss okumuraCalculation(const Sector &sector);
    Pathloss costCalculation(const Sector &sector);

    std::shared_ptr<IMapDataProvider> mapProvider;
    SectorsControler & sectors;
    const Receiver & receiver;
};

#endif // PATHLOSSCALCULATION_H
