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

private slots:
    void itemTreeDoubleClicked(QTreeWidgetItem*,int);
    void changeDataFor(QTreeWidgetItem*);

private:
    void showNetworkElements();
    QTreeWidgetItem* addTreeRoot(QString name, QString value);
    QTreeWidgetItem* addChildToRoot(QTreeWidgetItem* parent, QString name, QString value);
    void fillNetworElements();
    int findTypeOfField(QString);
    QTreeWidgetItem* findProperParent(QTreeWidgetItem* p_treeItem);
    void changeDataForENB(QTreeWidgetItem*, QTreeWidgetItem*);
    void changeDataForSector(QTreeWidgetItem *p_parent, QTreeWidgetItem* p_treeItem);

    void setupConnections();

    Ui::NetworkObjectWizualizator* ui;
    DataProvider& dataProvider;

    std::map<QTreeWidgetItem*, QString> eNbTreeMap;
    std::map<QTreeWidgetItem*, int> ecgiSectorTreeMap;
};

#endif // NETWORKOBJECTWIZUALIZATOR_H
