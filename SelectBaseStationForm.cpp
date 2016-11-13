#include "SelectBaseStationForm.h"
#include "ui_SelectBaseStationForm.h"
#include "DataProvider.h"

#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

SelectBaseStationForm::SelectBaseStationForm(const DataProvider & p_data,
                                             QWidget *parent) :
    QDialog(parent),
    data(p_data),
    selectedBaseStation(""),
    ui(new Ui::SelectBaseStationForm)
{
    ui->setupUi(this);
    ui->baseListView->setAutoScroll(true);
    setWindowModality(Qt::WindowModal);
    update();
}

SelectBaseStationForm::~SelectBaseStationForm()
{
    delete ui;
}

std::string SelectBaseStationForm::getSelectedBaseStation()
{
    if(selectedBaseStation != "")
    {
        return selectedBaseStation;
    }
    else return "";
}

void SelectBaseStationForm::accept()
{
    commit();
    emit baseStationSelected();
    QDialog::accept();
}

void SelectBaseStationForm::update()
{
    model = new QStringListModel(this);
    QStringList list;
    for(auto name : data.baseStations)
    {
        list << name->getName().c_str();
    }
    model->setStringList(list);
    ui->baseListView->setModel(model);
    ui->comboBox->setModel(model);

    ui->baseListView->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                      QAbstractItemView::DoubleClicked);
}

void SelectBaseStationForm::commit()
{
    selectedBaseStation = ui->comboBox->currentText().toStdString();
}
