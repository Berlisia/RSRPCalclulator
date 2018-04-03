#ifndef NETWORKOBJECTWIZUALIZATOR_H
#define NETWORKOBJECTWIZUALIZATOR_H

#include <QDialog>
#include <memory>
#include <QTreeWidget>

class DataProvider;
class QTreeWidgetItem;
class QComboBox;
class Sector;

namespace Ui {
class NetworkObjectWizualizator;
}

class NetworkObjectWizualizator : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkObjectWizualizator(QWidget* parent, QTreeWidget* p_ui, DataProvider& p_data);
    ~NetworkObjectWizualizator();

public slots:
    void update();

private slots:
    void itemTreeDoubleClicked(QTreeWidgetItem*,int);
    void changeDataFor(QTreeWidgetItem*);
    void changeDataForEnvComboBox(int);

private:
    void showNetworkElements();
    QTreeWidgetItem* addTreeRoot(QString name, QString value);
    QTreeWidgetItem* addChildToRoot(QTreeWidgetItem* parent, QString name, QString value);
    QTreeWidgetItem* addChildToRootWithSepcialWidget(QTreeWidgetItem* parent, QString name, QWidget* widget);
    void fillNetworElements();
    int findTypeOfField(QString);
    QTreeWidgetItem* findProperParent(QTreeWidgetItem* p_treeItem);
    void changeDataForENB(QTreeWidgetItem*, QTreeWidgetItem*);
    void changeDataForSector(QTreeWidgetItem *p_parent, QTreeWidgetItem* p_treeItem);

    QComboBox* createQComboBoxForSelectEnvironment(const Sector&);
    QComboBox* createQComboBoxForSelectMimo(const Sector&);
    QComboBox* createQComboBoxForSelectPropModel(const Sector&);

    void setupConnections();

    QTreeWidget* treeWidget;
    DataProvider& dataProvider;

    std::map<QTreeWidgetItem*, QString> eNbTreeMap;
    std::map<QTreeWidgetItem*, int> ecgiSectorTreeMap;
};

#endif // NETWORKOBJECTWIZUALIZATOR_H
