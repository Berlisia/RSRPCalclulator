#ifndef BASESTATIONFORM_H
#define BASESTATIONFORM_H

#include <QDialog>
#include <vector>
#include <memory>

class BaseStation;
class DataProvider;
class GeographicalCoordinatesConverter;
namespace Ui {
class BaseStationForm;
}

class SectorsControler;

class BaseStationForm : public QDialog
{
    Q_OBJECT

public:
    explicit BaseStationForm(GeographicalCoordinatesConverter const& p_geoConverter,
                             DataProvider & p_data, QWidget *parent = 0);
    ~BaseStationForm();

    std::shared_ptr<BaseStation> getBaseStation();

public slots:
    void accept();
    void update();
    void commit();

signals:
    void baseStationCreated();

private:
    GeographicalCoordinatesConverter const& geoConverter;
    DataProvider & data;
    Ui::BaseStationForm *ui;

    std::shared_ptr<BaseStation> baseStation;
};

#endif // BASESTATIONFORM_H
