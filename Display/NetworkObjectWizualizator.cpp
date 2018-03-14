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
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setAutoScroll(true);
    setWindowModality(Qt::NonModal);
    showNetworkElements();
}

NetworkObjectWizualizator::~NetworkObjectWizualizator()
{
    delete ui;
}

void NetworkObjectWizualizator::update()
{
    ui->treeWidget->clear();
    fillNetworElements();
    ui->treeWidget->show();
}

void NetworkObjectWizualizator::showNetworkElements()
{
    fillNetworElements();
}

QTreeWidgetItem* NetworkObjectWizualizator::addTreeRoot(QString name, QString value)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0, name);
    treeItem->setText(1, value);
    return treeItem;
}

QTreeWidgetItem* NetworkObjectWizualizator::addChildToRoot(QTreeWidgetItem* parent, QString name, QString value)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setText(1, value);
    parent->addChild(treeItem);
    return treeItem;
}

void NetworkObjectWizualizator::fillNetworElements()
{
    for(auto eNB : dataProvider.baseStations)
    {
        QTreeWidgetItem* currentTreeItem = addTreeRoot("eNB", eNB->getName().c_str());
        addChildToRoot(currentTreeItem, "Position", QString::number(eNB->getPossition().first) +
                                                    ", " +
                                                    QString::number(eNB->getPossition().second));
        currentTreeItem = addChildToRoot(currentTreeItem, "Height [m n.p.t]", QString::number(eNB->getAntennaHeight()));
        QTreeWidgetItem* sectorTreeItem = addChildToRoot(currentTreeItem, "Sectors", " ");
        for(auto sector : dataProvider.sectorControler->getVectorOfSectors())
        {
            int index = 1; //TODO dodaj nr sektora (np PCI)
            if(sector.getBaseStationName() == eNB->getName())
            {
                currentTreeItem = addChildToRoot(sectorTreeItem, "Sector", QString::number(index));
                index++;
                addChildToRoot(currentTreeItem, "Power [dB]", QString::number(sector.getPower()));
                addChildToRoot(currentTreeItem, "Band [MHz]", QString::number(sector.getFrequency()));
                addChildToRoot(currentTreeItem, "Bandwidth [MHz]", QString::number(sector.getBandwith()));
                addChildToRoot(currentTreeItem, "Azimuth [deegres]", QString::number(sector.getAzimuth()));
                addChildToRoot(currentTreeItem, "MIMO", QString::number(int(sector.getMimo()))); //TODO
                addChildToRoot(currentTreeItem, "Environment", QString::number(int(sector.getEnvironment())));
                addChildToRoot(currentTreeItem, "Propagation model", "TODO");

                currentTreeItem = addChildToRoot(currentTreeItem, "Antenna", " ");
                addChildToRoot(currentTreeItem, "Gain [dBi]", QString::number(sector.getGain()));
                addChildToRoot(currentTreeItem, "Tilt [deegres]", QString::number(sector.getAntennaTilt()));

                currentTreeItem = addChildToRoot(currentTreeItem, "Characteristics files", " ");
                addChildToRoot(currentTreeItem, "Horizontal", sector.getHorizontalFileName().c_str());
                addChildToRoot(currentTreeItem, "Vertical", sector.getVerticalFileName().c_str());
            }
        }

    }
}
