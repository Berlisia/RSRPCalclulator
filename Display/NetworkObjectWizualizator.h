#ifndef NETWORKOBJECTWIZUALIZATOR_H
#define NETWORKOBJECTWIZUALIZATOR_H

#include <QWidget>

namespace Ui {
class NetworkObjectWizualizator;
}

class NetworkObjectWizualizator : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkObjectWizualizator(QWidget *parent = 0);
    ~NetworkObjectWizualizator();

private:
    Ui::NetworkObjectWizualizator *ui;
};

#endif // NETWORKOBJECTWIZUALIZATOR_H
