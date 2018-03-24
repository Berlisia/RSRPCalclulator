#include "ui_NetworkObjectWizualizatorForm.h"
#include <QTreeWidget>
#include <QDebug>
#include <QComboBox>

#include "NetworkObjectWizualizator.h"
#include "DataProvider.h"
#include "GuiConstans.h"

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
    setupConnections();
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

namespace
{
bool isEditable(int p_colum)
{
    return (p_colum == 1);
}
}

void NetworkObjectWizualizator::itemTreeDoubleClicked(QTreeWidgetItem* p_treeItem, int p_colum)
{
    Qt::ItemFlags tmp = p_treeItem->flags();
    if (isEditable(p_colum))
    {
        p_treeItem->setFlags(tmp | Qt::ItemIsEditable);
    }
    else if (tmp & Qt::ItemIsEditable)
    {
        p_treeItem->setFlags(tmp ^ Qt::ItemIsEditable);
    }
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
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable);
    parent->addChild(treeItem);
    return treeItem;
}

QTreeWidgetItem* NetworkObjectWizualizator::addChildToRootWithSepcialWidget(QTreeWidgetItem* parent, QString name, QWidget* widget)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable);
    parent->addChild(treeItem);
    ui->treeWidget->setItemWidget(treeItem, 1, widget);
    return treeItem;
}

void NetworkObjectWizualizator::fillNetworElements()
{
    for(auto eNB : dataProvider.baseStations)
    {
        QTreeWidgetItem* currentTreeItem = addTreeRoot(GUI::eNbName, eNB->getName().c_str());
        eNbTreeMap[currentTreeItem] = QString(eNB->getName().c_str());
        addChildToRoot(currentTreeItem, GUI::position, QString::number(eNB->getPossition().first) +
                                                       ", " +
                                                       QString::number(eNB->getPossition().second));
        currentTreeItem = addChildToRoot(currentTreeItem, GUI::height, QString::number(eNB->getAntennaHeight()));

        QTreeWidgetItem* sectorTreeItem = addChildToRoot(currentTreeItem, GUI::sectors, " ");
        for(auto sector : dataProvider.sectorControler->getVectorOfSectors())
        {
            if(sector.getBaseStationName() == eNB->getName())
            {
                currentTreeItem = addChildToRoot(sectorTreeItem, GUI::sectorIdx, QString::number(sector.getEcgi()));
                ecgiSectorTreeMap[currentTreeItem] = sector.getEcgi();

                addChildToRoot(currentTreeItem, GUI::power, QString::number(sector.getPower()));
                addChildToRoot(currentTreeItem, GUI::band, QString::number(sector.getFrequency()));
                addChildToRoot(currentTreeItem, GUI::bandwidth, QString::number(sector.getBandwith()));

                addChildToRootWithSepcialWidget(currentTreeItem, GUI::mimo, createQComboBoxForSelectMimo(sector));
                addChildToRootWithSepcialWidget(currentTreeItem, GUI::environment, createQComboBoxForSelectEnvironment(sector));
                //connect(environmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeDataForEnvComboBox(int)));
                addChildToRootWithSepcialWidget(currentTreeItem, GUI::propModel, createQComboBoxForSelectPropModel(sector));

                currentTreeItem = addChildToRoot(currentTreeItem, GUI::antenna, "");
                addChildToRoot(currentTreeItem, GUI::gain, QString::number(sector.getGain()));
                addChildToRoot(currentTreeItem, GUI::azimuth, QString::number(sector.getAzimuth()));
                addChildToRoot(currentTreeItem, GUI::tilt, QString::number(sector.getAntennaTilt()));

                currentTreeItem = addChildToRoot(currentTreeItem, GUI::charFiles, "");
                addChildToRoot(currentTreeItem, GUI::fileH, sector.getHorizontalFileName().c_str());
                addChildToRoot(currentTreeItem, GUI::fileV, sector.getVerticalFileName().c_str());
            }
        }
    }
}

QTreeWidgetItem* NetworkObjectWizualizator::findProperParent(QTreeWidgetItem* p_treeItem)
{
    switch (findTypeOfField(p_treeItem->text(0)))
    {
    case E_NB_ID:
        return p_treeItem;
    case POSITION:
    case HEIGHT:
       return p_treeItem->parent();
    case SECTOR_ID:
        return p_treeItem;
    case POWER:
    case BAND:
    case BANDWIDTH:
    case MIMO:
    case ENVIRNOMENT:
    case PROPAGATION_MODEL:
        return p_treeItem->parent();
    case GAIN:
    case TILT:
    case AZIMUT:
        return p_treeItem->parent()->parent();
    case FILE_V:
    case FILE_H:
        return p_treeItem->parent()->parent()->parent();
    }
    return nullptr;
}

void NetworkObjectWizualizator::changeDataForENB(QTreeWidgetItem *p_parent, QTreeWidgetItem *p_itemChanged)
{
    auto p_enbId = eNbTreeMap[p_parent];
    dataProvider.updateInputValueForBaseStation(p_enbId, p_itemChanged->text(0), p_itemChanged->text(1));
    if(p_parent == p_itemChanged) eNbTreeMap[p_parent] = p_itemChanged->text(1);
}

void NetworkObjectWizualizator::changeDataForSector(QTreeWidgetItem *p_parent, QTreeWidgetItem *p_treeItem)
{
    auto ecgi = ecgiSectorTreeMap[p_parent];
    qDebug() << "zmiana: " << p_treeItem->text(1);
    dataProvider.updateInputValueForSector(ecgi, p_treeItem->text(0), p_treeItem->text(1));
    if(p_parent == p_treeItem) ecgiSectorTreeMap[p_parent] = p_treeItem->text(1).toInt();
}

QComboBox* NetworkObjectWizualizator::createQComboBoxForSelectEnvironment(const Sector& sector)
{
    QComboBox* environmentComboBox = new QComboBox(this);
    environmentComboBox->addItem("Small and medium size cities", QVariant(SMALL_AND_MEDIUM_SIZE_CITIES));
    environmentComboBox->addItem("Metropolitan areas", QVariant(METROPOLITAN_AREAS));
    environmentComboBox->addItem("Suburban evironments", QVariant(SUBURBAN_ENV));
    environmentComboBox->addItem("Rural aera", QVariant(RURAL_AREA));
    environmentComboBox->setCurrentIndex(int(sector.getEnvironment()) - 1);
    return environmentComboBox;
}

QComboBox* NetworkObjectWizualizator::createQComboBoxForSelectMimo(const Sector& sector)
{
    QComboBox* mimoBox = new QComboBox(this);
    mimoBox->addItem("Nan", QVariant(0));
    mimoBox->addItem("2x2", QVariant(1));
    mimoBox->addItem("4x4", QVariant(2));
    mimoBox->setCurrentIndex(int(sector.getMimo()));
    return mimoBox;
}

QComboBox *NetworkObjectWizualizator::createQComboBoxForSelectPropModel(const Sector& sector)
{
    QComboBox* modelBox = new QComboBox(this);
    modelBox->addItem("Okumura Hata", QVariant(0));
    modelBox->addItem("Cost231 Hata", QVariant(1));
    modelBox->setCurrentIndex(int(sector.getModel()));
    return modelBox;

}

void NetworkObjectWizualizator::changeDataFor(QTreeWidgetItem* p_treeItem)
{
    QTreeWidgetItem* parent = findProperParent(p_treeItem);
    if(!parent) return;
    if(parent->text(0) == GUI::sectorIdx)
    {
        changeDataForSector(parent, p_treeItem);
    }
    else if(parent->text(0) == GUI::eNbName)
    {
        changeDataForENB(parent, p_treeItem);
    }
}

void NetworkObjectWizualizator::changeDataForEnvComboBox(int index)
{
    qDebug() << "change ComboBox" << index;
}

int NetworkObjectWizualizator::findTypeOfField(QString p_field)
{
    return GUI::behaviorMap.find(p_field)->second;
}

void NetworkObjectWizualizator::setupConnections()
{
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemTreeDoubleClicked(QTreeWidgetItem*,int)));
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(changeDataFor(QTreeWidgetItem*)));
}
