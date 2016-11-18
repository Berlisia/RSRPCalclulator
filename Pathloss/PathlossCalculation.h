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
    float effectiveBAntennaHeight(Sector const& sector);
    ~PathlossCalculation(){}

private:
    void setUpParameters(PathlossModel & model, Sector const& sector);
    Model choosePropagarionModel(const Sector &sector);
    Pathloss okumuraCalculation(const Sector &sector);
    Pathloss costCalculation(const Sector &sector);

    std::shared_ptr<IMapDataProvider> mapProvider;
    SectorsControler & sectors;
    Receiver & receiver;

    std::unique_ptr<PathlossModel> okumuryModel;
    std::unique_ptr<PathlossModel> hataModel;

};

#endif // PATHLOSSCALCULATION_H
