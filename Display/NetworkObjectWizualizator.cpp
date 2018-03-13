#include "ui_NetworkObjectWizualizatorForm.h"
#include <QTreeWidget>

#include "NetworkObjectWizualizator.h"
#include "DataProvider.h"

NetworkObjectWizualizator::NetworkObjectWizualizator(QWidget* parent, DataProvider& p_data) :
    QDialog(parent),
    ui(new Ui::NetworkObjectWizualizator),
    dataProvider(p_data)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    showNetworkElements();
}

NetworkObjectWizualizator::~NetworkObjectWizualizator()
{
    delete ui;
}

void NetworkObjectWizualizator::update()
{

}

void NetworkObjectWizualizator::showNetworkElements()
{
    addTreeRoot("dupa");
}

void NetworkObjectWizualizator::addTreeRoot(QString name)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0, name);
    addChildToRoot(treeItem, "rowek");
}

void NetworkObjectWizualizator::addChildToRoot(QTreeWidgetItem* parent, QString name)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
    QTreeWidgetItem* treeItemchild = new QTreeWidgetItem();
    treeItemchild->setText(0,"roweczek");
    treeItem->addChild(treeItemchild);
}
