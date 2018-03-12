#include "NetworkObjectWizualizator.h"
#include "ui_NetworkObjectWizualizatorForm.h"

NetworkObjectWizualizator::NetworkObjectWizualizator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkObjectWizualizator)
{
    ui->setupUi(this);
}

NetworkObjectWizualizator::~NetworkObjectWizualizator()
{
    delete ui;
}
