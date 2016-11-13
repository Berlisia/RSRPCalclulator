#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BaseStationForm.h"
#include "SectorForm.h"
#include "SelectBaseStationForm.h"
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <algorithm>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTreeWidgetItem>
#include "ImagePainter.h"
#include "Worker.h"

using namespace std;

MainWindow::MainWindow(DataProvider & p_data, const Worker * p_worker, QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    data(p_data)
{
    ui->setupUi(this);
    QPixmap img;
    img.load("asd.pgm");
    displayImage(img);

    QWidget::setWindowTitle("RSRP Calculator @created by Ewelina Berlicka");

    addMenu();

    connect(ui->baseToolButton, SIGNAL(pressed()), this, SLOT(on_baseStationUi_clicked()));
    connect(ui->sectorToolButton, SIGNAL(pressed()), this, SLOT(selectBase()));
    connect(ui->calculatePushButton, SIGNAL(pressed()), p_worker, SLOT(doCalculation()));
    connect(p_worker, SIGNAL(done()), this, SLOT(drawImage()));
}

void MainWindow::closeEvent(QCloseEvent * event)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayImage(const QPixmap & img)
{
    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem(img);
    scene->addItem(item);
    QSize size = ui->mapGraphicsView->size();
    ui->mapGraphicsView->setScene(scene);
    ui->mapGraphicsView->show();
}

void MainWindow::addMenu()
{
    QMenu * mainMenu = new QMenu(tr("&Menu"), this);
    QMenu * tools = new QMenu(tr("&Tools"), this);

    QMainWindow::menuBar()->addMenu(mainMenu);
    mainMenu->addAction(tr("&Quit"), this, SLOT(close()));

    QMainWindow::menuBar()->addMenu(tools);
    tools->addAction(tr("&Add Base Station"), this, SLOT(on_baseStationUi_clicked()), tr("Ctrl+B"));
    tools->addAction(tr("&View created objects"), this, SLOT(on_viewCreatedObject_clicked()), tr("&Ctrl+V"));
}

void MainWindow::drawImage()
{
    ImagePainter paint(data.rsrp, this);
    QPixmap px;
    px.load("asd.ppm");
    QPainter painter(&px);
    float max = paint.findMax();
    float min = paint.findMin();
    float roznica = max - min;
    float wspolczynnik = 100/roznica;
    for(auto dat : data.rsrp)
    {
        float color = (dat.second - min)*wspolczynnik;
        painter.setPen(paint.getColor(color));
        painter.drawPoint(dat.first.getX(), dat.first.getY());
    }
    painter.end();
    displayImage(px);
}

void MainWindow::selectBase()
{
    if(!selectBaseStation)
    {
        selectBaseStation = std::make_unique<SelectBaseStationForm>(data, this);
        connect(selectBaseStation.get(), SIGNAL(baseStationSelected()), this, SLOT(on_sectorUI_clliced()));
    }
    else
    {
        selectBaseStation->update();
    }
    selectBaseStation->show();
}

void MainWindow::updateTree()
{
    ui->treeWidget->clear();
    std::vector<std::shared_ptr<QTreeWidgetItem> > treeItems;
    for(auto base : data.baseStations)
    {
        std::shared_ptr<QTreeWidgetItem> treeItem =
                std::make_shared<QTreeWidgetItem>(ui->treeWidget);
        addTreeRoot(treeItem , base->getName().c_str(), "Stacja Bazowa");
        treeItems.push_back(treeItem);
    }
    for(auto sector : data.sectorControler->getVectorOfSectors())
    {
        QString name(sector.getBaseStationName().c_str());
        QList<QTreeWidgetItem*> items = ui->treeWidget->findItems(name, Qt::MatchExactly, 0);
        addTreeChild(items.front(), "Power", QVariant(sector.getPower()).toString());
    }
}

BaseStations::iterator MainWindow::getIndexOfBaseStation()
{
    BaseStations::iterator it;
    std::string key = selectBaseStation->getSelectedBaseStation();

    it = std::find_if(data.baseStations.begin(), data.baseStations.end(),
                      [key](std::shared_ptr<BaseStation> base) -> bool {
                            return base->getName() == key;
    });
    return it;
}

void MainWindow::setTreeView()
{
    ui->treeWidget->setColumnCount(2);
}

void MainWindow::addTreeRoot(std::shared_ptr<QTreeWidgetItem> treeItem, QString name, QString description)
{
    treeItem->setText(0, name);
    treeItem->setText(1, description);
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent, QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    parent->addChild(treeItem);
}

void MainWindow::on_actionUndo_The_Last_Action_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_saveButton_clicked()
{

}

void MainWindow::on_undoButton_clicked()
{

}

void MainWindow::on_baseStationUi_clicked()
{
    baseStationForm = make_unique<BaseStationForm>(data, this);
    connect(baseStationForm.get(), SIGNAL(baseStationCreated()), this, SLOT(updateTree()));
    baseStationForm->show();
}

void MainWindow::on_viewCreatedObject_clicked()
{

}

void MainWindow::on_sectorUI_clliced()
{
    if (baseStationForm)
    {
        sectorForm = make_unique<SectorForm>(data.sectorControler, *getIndexOfBaseStation(), this);
        connect(sectorForm.get(), SIGNAL(sectorCreated()), this, SLOT(updateTree()));
        sectorForm->show();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You must add base station!");
        messageBox.setFixedSize(500,200);
    }
}
