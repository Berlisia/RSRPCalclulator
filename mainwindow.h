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
#include "TerrainProfile.h"
#include <QProgressBar>

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
class ImagePainter;
class Worker;
class ReceiverForm;
class NetworkObjectWizualizator;
class QGraphicsSceneMouseEvent;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DataProvider& p_data, std::shared_ptr<IMapDataProvider> p_mapData, QWidget *parent = 0);
    void closeEvent(QCloseEvent * event);
    ~MainWindow();

signals:
    void calculationButtonPressed();

public slots:
    void displayImage(const QPixmap & img, std::vector<std::pair<PixelXY,double>>&);
    void drawDataMap();
    void updateProgressBar(unsigned progress);
    void setProgressBarRange(unsigned max);

private:
    void addMenu();
    BaseStations::iterator getIndexOfBaseStation();
    void showScale(ImagePainter &paint, double max, double min);
    void setPixelsArea(QRectF rect);
    void networkWizualizatorStart();
    void radioBoxesCheckable();
    void setUpImagesRadioBoxes();
    RadioButtonType chooseTurnOnButton();

    Ui::MainWindow *ui;
    DataProvider & data;

    QGraphicsScene * scene;
    QGraphicsPixmapItem * item;

    QGraphicsScene * scaleScene;
    QGraphicsPixmapItem * scaleItem;

    std::shared_ptr<IMapDataProvider> mapDataProvider;

    std::unique_ptr<NetworkObjectWizualizator> networkWizualizator;
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

    unsigned initBarSize;
    double maxFromData;
    double minFromData;
    QProgressBar progressBar;

private slots:
    void on_baseStationUi_clicked();
    void on_sectorUI_clliced();

    void selectBase();
    void drawImage(std::vector<std::pair<PixelXY,double>>&);
    void drawInterferenceImage(bool);
    void drawSnirImage(bool);
    void drawSignalImg(bool);
    void drawModulationImg(bool enabled);
    void drawRsrqImg(bool);

    void receiverClicked();
    void changeMinRSRPValueInData(double);

    void actionRectangleTriggered();
    void showRectangle();
    void drawTerrainLine();
    void drawBaseStationPossition();
    void zoomIn();
    void zoomOut();
    void terrainProfileTriggered(bool);
    void saveLineData();
};

#endif // MAINWINDOW_H
