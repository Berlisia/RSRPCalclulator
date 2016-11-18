#include "SectorForm.h"
#include "ui_SectorForm.h"
#include "Core/Antenna.h"
#include "AntennaLoss/AntennaLossFileProvider.h"
#include "Core/SectorsControler.h"
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QMessageBox>

SectorForm::SectorForm(std::shared_ptr<SectorsControler> p_sectors,
                       std::shared_ptr<BaseStation> p_baseStation,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SectorForm),
    sectors(p_sectors),
    baseStation(p_baseStation),
    nameHorizontalFile(""),
    nameVerticalFile("")
{
    ui->setupUi(this);
    ui->azimuthSpinBox->setMaximum(359);
    ui->bandSpinBox->setMaximum(5000);
    ui->powerDoubleSpinBox->setMaximum(1000);
    ui->tiltSpinBox->setMaximum(180);

    connect(ui->HorizontalToolButton, SIGNAL(pressed()), this, SLOT(applayHorizontalFile()));
    connect(ui->VerticalToolButton, SIGNAL(pressed()), this, SLOT(applayVerticalFile()));
    connect(ui->bandSpinBox, SIGNAL(valueChanged(int)), this, SLOT(editRadioBoxes(int)));

    setVariatforBandwidth();
    setVariantForMimo();
    setVariantForEnvironent();
}

SectorForm::~SectorForm()
{
    delete ui;
}

void SectorForm::accept()
{
    commit();
    emit sectorCreated();
    QDialog::accept();
}

void SectorForm::commit()
{
    errorMessageForUncheckRadioBoxes();
    Antenna antenna(ui->powerDoubleSpinBox->value(),
                    ui->tiltSpinBox->value(),
                    ui->bandSpinBox->value(),
                    nameHorizontalFile,
                    nameVerticalFile);
    createAntennaProvider();

    Sector sector(antenna, baseStation);
    sector.setBandwidth(ui->bandwidthBox->itemData(ui->bandwidthBox->currentIndex()).toDouble());
    sector.setAzimuth(ui->azimuthSpinBox->value());
    sector.setMimo(convertQMimo(ui->mimoBox->currentIndex())); //TODO dodaj w obliczeniach i konwersje do MIMO
    sector.setEnvironment(converQEnvironment(ui->environmentComboBox->currentIndex()));
    chooseModel(sector);
    sectors->addSector(sector);
}

void SectorForm::applayHorizontalFile()
{
    nameHorizontalFile = QFileDialog::getOpenFileName().toStdString();
}

void SectorForm::applayVerticalFile()
{
    nameVerticalFile = QFileDialog::getOpenFileName().toStdString();
}

void SectorForm::editRadioBoxes(int band)
{
    if(band > 1500)
    {
        ui->okumyraRadioButton->setEnabled(false);
    }
    else
    {
        ui->okumyraRadioButton->setEnabled(true);
        ui->costRadioButton->setEnabled(true);
    }
}

void SectorForm::createAntennaProvider()
{
    antennaProvider = std::make_shared<AntennaLossFileProvider>(nameHorizontalFile,
                                                                nameVerticalFile);
}

void SectorForm::setVariatforBandwidth()
{
    ui->bandwidthBox->addItem("1,4 MHz", QVariant(1.4));
    ui->bandwidthBox->addItem("3,0 MHz", QVariant(3.0));
    ui->bandwidthBox->addItem("5,0 MHz", QVariant(5.0));
    ui->bandwidthBox->addItem("10,0 MHz", QVariant(10.0));
    ui->bandwidthBox->addItem("15,0 MHz", QVariant(15.0));
    ui->bandwidthBox->addItem("20,0 MHz", QVariant(20.0));
}

void SectorForm::setVariantForMimo() //TODO
{
    ui->mimoBox->addItem("Nan", QVariant(0));
    ui->mimoBox->addItem("2x2", QVariant(1));
    ui->mimoBox->addItem("4x4", QVariant(2));
}

void SectorForm::setVariantForEnvironent()
{
    ui->environmentComboBox->addItem("Small and medium size cities", QVariant(0));
    ui->environmentComboBox->addItem("Metropolitan areas", QVariant(1));
    ui->environmentComboBox->addItem("Suburban evironments", QVariant(2));
    ui->environmentComboBox->addItem("Rural aera", QVariant(3));
}

void SectorForm::chooseModel(Sector & sector)
{
    if(ui->okumyraRadioButton->isChecked())
        sector.setModel(Model::OkumuraHata);
    else if(ui->costRadioButton->isChecked())
        sector.setModel(Model::Cost231Hata);
}

bool SectorForm::errorMessageForUncheckRadioBoxes()
{
    if(!ui->okumyraRadioButton->isChecked() and !ui->costRadioButton->isChecked())
    {
        QMessageBox messageBox;
        messageBox.information(this,"Error","Choose propagation model!");
        messageBox.setFixedSize(500,200);
    }
    return false;
}

Environment SectorForm::converQEnvironment(int index)
{
    switch (index)
    {
    case 0:
        return Environment::SmallAndMediumSizeCities;
    case 1:
        return Environment::MetropolitanAreas;
    case 2:
        return Environment::SuburbanEvironments;
    case 3:
        return Environment::RuralAera;
    default:
        return Environment::Idle;
    }
}

MIMO SectorForm::convertQMimo(int index)
{
    switch(index)
    {
    case 0:
        return MIMO::Nan;
    case 1:
        return MIMO::TwoAntenna;
    case 2:
        return MIMO::FourAntenna;
    default:
        return MIMO::Nan;
    }
}


