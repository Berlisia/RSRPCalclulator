#include "BaseStationForm.h"
#include "ui_BaseStationForm.h"
#include "Core/PixelXY.h"
#include "Core/BaseStation.h"
#include "DataProvider.h"

using namespace std;

BaseStationForm::BaseStationForm(DataProvider &p_data, QWidget *parent) :
    QDialog(parent),
    data(p_data),
    ui(new Ui::BaseStationForm)
{
    ui->setupUi(this);
    ui->xSpinBox->setMaximum(3802);
    ui->ySpinBox->setMaximum(3942);
    ui->heightBox->setMaximum(1000);
}

BaseStationForm::~BaseStationForm()
{
    delete ui;
}

std::shared_ptr<BaseStation> BaseStationForm::getBaseStation()
{
    return baseStation;
}

void BaseStationForm::accept()
{
    commit();
    emit baseStationCreated();
    QDialog::accept();
}

void BaseStationForm::update()
{

}

void BaseStationForm::commit()
{
    PixelXY possition(ui->xSpinBox->value(), ui->ySpinBox->value());
    baseStation = make_shared<BaseStation>(std::move(possition.getXy()),
                                           ui->heightBox->value(),
                                           ui->nameLineEdit->text().toStdString());
    data.addBaseStation(baseStation);
}

void BaseStationForm::on_AntennasView_currentChanged(int index)
{

}

void BaseStationForm::on_addSector_triggered()
{

}
