#ifndef NETWORKOBJECTWIZUALIZATOR_H
#define NETWORKOBJECTWIZUALIZATOR_H

#include <QDialog>
#include <memory>

class DataProvider;
class QTreeWidgetItem;

namespace Ui {
class NetworkObjectWizualizator;
}

class NetworkObjectWizualizator : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkObjectWizualizator(QWidget* parent, DataProvider& p_data);
    ~NetworkObjectWizualizator();

public slots:
    void update();
private:
    void showNetworkElements();
    void addTreeRoot(QString name);
    void addChildToRoot(QTreeWidgetItem* parent, QString name);

    Ui::NetworkObjectWizualizator* ui;
    DataProvider& dataProvider;
};

#endif // NETWORKOBJECTWIZUALIZATOR_H
