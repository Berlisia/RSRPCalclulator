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
    QTreeWidgetItem* addTreeRoot(QString name, QString value);
    QTreeWidgetItem* addChildToRoot(QTreeWidgetItem* parent, QString name, QString value);
    void fillNetworElements();

    Ui::NetworkObjectWizualizator* ui;
    DataProvider& dataProvider;
};

#endif // NETWORKOBJECTWIZUALIZATOR_H
