#ifndef SECTORFORM_H
#define SECTORFORM_H

#include <QDialog>
#include <memory>

class IAntennaLossFileProvider;
class SectorsControler;
class BaseStation;
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

private:
    void createAntennaProvider();
    void setVariatforBandwidth();
    void setVariantForMimo();

    Ui::SectorForm *ui;
    std::shared_ptr<IAntennaLossFileProvider> antennaProvider;
    std::shared_ptr<SectorsControler> sectors;
    std::shared_ptr<BaseStation> baseStation;

    std::string nameHorizontalFile;
    std::string nameVerticalFile;

    MIMO convertQMimo(int index);
};

#endif // SECTORFORM_H
