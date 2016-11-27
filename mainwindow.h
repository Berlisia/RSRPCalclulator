#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <memory>
#include <QAction>
#include "DataProvider.h"
#include "ScribbleArea.h"
#include "DrawRectangle.h"
#include "Canvas.h"
#include "MapProvider/GeographicalCoordinatesConverter.h"

class QWidget;
class QLabel;
class QImage;
class QEvent;
class SectorForm;
class BaseStationForm;
class SelectBaseStationForm;
class QGraphicsScene;
class QGraphicsView;
class QGraphicsPixmapItem;
class QTreeWidgetItem;
class ImagePainter;
class Worker;
class ReceiverForm;
class QGraphicsSceneMouseEvent;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DataProvider & p_data, const Worker * p_worker, QWidget *parent = 0);
    void closeEvent(QCloseEvent * event);
    ~MainWindow();

    void addTreeRoot(std::shared_ptr<QTreeWidgetItem> treeItem, QString name, QString description);
    void addTreeChild(QTreeWidgetItem * parent, QString name, QString description);

signals:
    void calculatePressed();

public slots:
    void displayImage(const QPixmap & img);

private:
    void addMenu();
    BaseStations::iterator getIndexOfBaseStation();
    void setTreeView();
    void barFinished();
    void showScale(ImagePainter &paint, float max, float min);
    void setPixelsArea(QRectF rect);

    Ui::MainWindow *ui;
    QUndoStack m_Stack;
    DataProvider & data;

    QGraphicsScene * scene;
    QGraphicsPixmapItem * item;

    QGraphicsScene * scaleScene;
    QGraphicsPixmapItem * scaleItem;

    const Worker * worker;

    std::unique_ptr<BaseStationForm> baseStationForm;
    std::unique_ptr<SectorForm> sectorForm;
    std::unique_ptr<SelectBaseStationForm> selectBaseStation;
    std::unique_ptr<ReceiverForm> receiver;

    std::unique_ptr<ImagePainter> paint;
    ScribbleArea * mapArea;

    std::unique_ptr<DrawRectangle> drawRectangle;
    std::unique_ptr<QPainter> rectanglePainter;
    std::shared_ptr<QPixmap> areaCalculationPixmap;
    Canvas * canvas;

    QGraphicsItem * currenItemInScene;
    GeographicalCoordinatesConverter geoConverter;
    std::shared_ptr<TerrainProfile> terProfile;

    int initBarSize;
    float maxFromData;
    float minFromData;

private slots:
    void on_baseStationUi_clicked();
    void on_sectorUI_clliced();

    void selectBase();
    void updateTree();
    void drawImage();

    void barChanged();
    void progressBarStart();
    void receiverClicked();
    void changeMinRSRPValueInData(double);
    void updateMap(int);

    void actionRectangleTriggered();
    void showRectangle();
    void drawTerrainLine();
    void drawBaseStationPossition();
    void zoomIn();
    void zoomOut();
    void terrainProfileTriggered(bool);

};

#endif // MAINWINDOW_H
