#include "BaseStationUI.h"

BaseStationUI::BaseStationUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseStationUI)
{
    ui->setupUi(this);
    connect(parent, buttonHasPressed(), this, show());
}

BaseStationUI::~BaseStationUI()
{
    delete ui;
}

void BaseStationUI::setConnects()
{

}
