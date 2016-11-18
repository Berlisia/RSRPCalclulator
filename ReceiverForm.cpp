#include "ReceiverForm.h"
#include "ui_ReceiverForm.h"
#include "DataProvider.h"

ReceiverForm::ReceiverForm(DataProvider & p_data, QWidget *parent) :
    QDialog(parent),
    data(p_data),
    ui(new Ui::ReceiverForm)
{
    ui->setupUi(this);
}

ReceiverForm::~ReceiverForm()
{
    delete ui;
}

void ReceiverForm::accept()
{
    commit();
    //emit receiverHeightChanged();
    QDialog::accept();
}

void ReceiverForm::update()
{
}

void ReceiverForm::commit()
{
    data.receiver.setHeight(ui->receiverSpinBox->value());
}
