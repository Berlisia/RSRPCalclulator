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
#include <QGraphicsSceneMouseEvent>
#include "ImagePainter.h"
#include <QMouseEvent>
#include "ReceiverForm.h"
#include "Worker.h"

using namespace std;

MainWindow::MainWindow(DataProvider & p_data, const Worker * p_worker, QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    data(p_data),
    scene(nullptr),
    worker(p_worker)
{
    ui->setupUi(this);
    QPixmap img;
    img.load("asd.ppm");
    displayImage(img);

    QWidget::setWindowTitle("RSRP Calculator @created by Ewelina Berlicka");

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    //ui->progressBar->hide();

    ui->label2->hide();
    ui->label3->hide();;
    ui->label4->hide();
    ui->maxLabel->setText(" ");
    ui->minLabel->setText(" ");
    ui->scalaGraphicsView->hide();
    ui->valueLabel->setText(" ");
    ui->minRSRPFromSlider->setText("0");
    ui->minimumRSRSPdoubleSpinBox->setRange(-200,0);
    ui->minimumRSRSPdoubleSpinBox->setValue(-140);
    ui->minRSRPFromSlider_2->setText("-140");

    ui->rsrpHorizontalSlider->setTickPosition(QSlider::TicksRight);
    ui->rsrpHorizontalSlider->setSingleStep(1);
    ui->rsrpHorizontalSlider->setMinimum(-140);
    ui->rsrpHorizontalSlider->setMaximum(0);

    addMenu();

    connect(ui->baseToolButton, SIGNAL(pressed()), this, SLOT(on_baseStationUi_clicked()));
    connect(ui->sectorToolButton, SIGNAL(pressed()), this, SLOT(selectBase()));
    connect(ui->calculatePushButton, SIGNAL(pressed()), p_worker, SLOT(doCalculation()));
    connect(p_worker, SIGNAL(done()), this, SLOT(drawImage()));
    connect(&data.rsrp, SIGNAL(rsrpSizeChanged()), this, SLOT(barChanged()));
    connect(worker, SIGNAL(poolStarted()), this, SLOT(progressBarStart()));
    connect(ui->receiverButton, SIGNAL(pressed()), this, SLOT(receiverClicked()));
    connect(ui->minimumRSRSPdoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changeMinRSRPValueInData(double)));
    connect(ui->rsrpHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(updateMap(int)));
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
    if(scene != nullptr)
        scene->clear();
    scene = new QGraphicsScene();
    mapArea = new ScribbleArea(ui->checkBox, data, ui->valueLabel,img);
    mapArea->setFlags(QGraphicsItem::ItemIsMovable);
    scene->addItem(mapArea);
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
    ui->progressBar->setValue(100);
    ImagePainter paint(data.rsrp.vector, this);
    QPixmap px;
    px.load("asd.ppm");
    QPainter painter(&px);
    maxFromData = paint.findMax();
    minFromData = paint.findMin();
    float roznica = maxFromData - minFromData;
    float wspolczynnik = 100/roznica;
    for(auto dat : data.rsrp.vector)
    {
        float color = (dat.second - minFromData)*wspolczynnik;
        painter.setPen(paint.getColor(color));
        painter.drawPoint(dat.first.getX(), dat.first.getY());
    }
    painter.end();
    displayImage(px);
    barFinished();
    showScale(paint, maxFromData, minFromData);
}

void MainWindow::barFinished()
{
    ui->progressBar->hide();
}

void MainWindow::showScale(ImagePainter & paint, float max, float min)
{
    QPixmap px;
    px.load("scala.ppm");
    QPainter painter(&px);

    for(int i = 1; i <= 200; i++)
    {
        painter.setPen(paint.getColor(i*0.5));
        painter.drawLine(10,i,50,i);
    }
    painter.end();

    scaleScene = new QGraphicsScene();
    scaleItem = new QGraphicsPixmapItem(px);
    scaleScene->addItem(scaleItem);

    ui->scalaGraphicsView->setScene(scaleScene);
    std::string Str = to_string(min) + "[dBm] ";
    ui->minLabel->setText(Str.c_str());
    ui->label2->setText(" ");
    ui->label2->show();
    ui->label3->setText(" ");
    ui->label3->show();
    ui->label4->setText(" ");
    ui->label4->show();
    Str = to_string(max) + "[dBm] ";
    ui->maxLabel->setText(Str.c_str());
    ui->scalaGraphicsView->show();
}

void MainWindow::createActions()
{
}

void MainWindow::barChanged()
{
    int size = worker->getQueueSize();
    ui->progressBar->setValue(size/initBarSize);
}

void MainWindow::progressBarStart()
{
    ui->progressBar->show();
    initBarSize = worker->getQueueSize();
}

void MainWindow::receiverClicked()
{
    if(!receiver)
    {
        receiver = std::make_unique<ReceiverForm>(data,this);
    }
    receiver->show();
}

void MainWindow::changeMinRSRPValueInData(double minRsrpValue)
{
    data.minValueOfRSRP = minRsrpValue;
    ui->rsrpHorizontalSlider->setMinimum(minRsrpValue);
    ui->minRSRPFromSlider_2->setText(to_string(minRsrpValue).c_str());
}

void MainWindow::updateMap(int slideValue)
{
    ui->minRSRPFromSlider->setText(to_string(slideValue).c_str());
    ImagePainter paint(data.rsrp.vector, this);
    QPixmap px;
    px.load("asd.ppm");
    QPainter painter(&px);
    float roznica = maxFromData - minFromData;
    float wspolczynnik = 100/roznica;
    for(auto dat : data.rsrp.vector)
    {
        if(dat.second >= slideValue)
        {
            float color = (dat.second - minFromData)*wspolczynnik;
            painter.setPen(paint.getColor(color));
            painter.drawPoint(dat.first.getX(), dat.first.getY());
        }
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
    ui->treeWidget->show();
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
