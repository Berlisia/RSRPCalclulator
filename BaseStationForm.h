#ifndef BASESTATIONFORM_H
#define BASESTATIONFORM_H

#include <QDialog>
#include <vector>
#include <memory>

class BaseStation;
class DataProvider;
namespace Ui {
class BaseStationForm;
}

class SectorsControler;

class BaseStationForm : public QDialog
{
    Q_OBJECT

public:
    explicit BaseStationForm(DataProvider & p_data, QWidget *parent = 0);
    ~BaseStationForm();

    std::shared_ptr<BaseStation> getBaseStation();

public slots:
    void accept();
    void update();
    void commit();

signals:
    void baseStationCreated();

private slots:
    void on_AntennasView_currentChanged(int index);
    void on_addSector_triggered();

private:
    DataProvider & data;
    Ui::BaseStationForm *ui;

    std::shared_ptr<BaseStation> baseStation;
};

#endif // BASESTATIONFORM_H
