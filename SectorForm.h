#ifndef SECTORFORM_H
#define SECTORFORM_H
#include "Pathloss/PathlossModel.h"

#include <QDialog>
#include <memory>

class IAntennaLossFileProvider;
class SectorsControler;
class BaseStation;
class Sector;
enum class MIMO;
namespace Ui {
class SectorForm;
}

class SectorForm : public QDialog
{
    Q_OBJECT

public:
    explicit SectorForm(std::shared_ptr<SectorsControler> p_sectors,
                        std::shared_ptr<BaseStation> p_baseStation,
                        QWidget *parent = 0);
    ~SectorForm();

signals:
    void sectorCreated();

public slots:
    void accept();
    void commit();

private slots:
    void applayHorizontalFile();
    void applayVerticalFile();
    void editRadioBoxes(int band);

private:
    void createAntennaProvider();
    void setVariatforBandwidth();
    void setVariantForMimo();
    void setVariantForEnvironent();
    void chooseModel(Sector & sector);
    bool errorMessageForUncheckRadioBoxes();
    bool antennaFileProviderIsInMemory();
    std::shared_ptr<IAntennaLossFileProvider> findSuitableCharacteristic();
    Environment converQEnvironment(int index);

    Ui::SectorForm *ui;
    std::shared_ptr<IAntennaLossFileProvider> antennaProvider;
    std::shared_ptr<SectorsControler> sectors;
    std::shared_ptr<BaseStation> baseStation;

    std::string nameHorizontalFile;
    std::string nameVerticalFile;

    Mimo convertQMimo(int index);
};

#endif // SECTORFORM_H
