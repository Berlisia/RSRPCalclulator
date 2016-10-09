#ifndef BASESTATIONUI_H
#define BASESTATIONUI_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class BaseStationUI;
}
class BaseStationUI : public QDialog
{
    Q_OBJECT

public:
    explicit BaseStationUI(QWidget *parent = 0);
    ~BaseStationUI();

    void setConnects();
private:
    Ui::BaseStationUI *ui;
};

#endif // BASESTATIONUI_H
