#ifndef TERRAINPROFILE_H
#define TERRAINPROFILE_H
#include "TerrainCanvas.h"
#include "Core/PixelXY.h"
#include "MapProvider/IMapDataProvider.h"
#include <memory>
#include <vector>
#include <QDialog>
#include "DataProvider.h"

class QGraphicsScene;
class QGraphicsPixmapItem;
class QGraphicsSceneMouseEvent;

enum class RadioButtonType
{
    null,
    RSRP,
    RSSI,
    RSRQ,
    SNIR,
    CQI
};

namespace Ui {
class TerrainProfile;
}

class TerrainProfile : public QDialog
{
    Q_OBJECT

public:
    explicit TerrainProfile(const DataProvider &p_data, std::shared_ptr<IMapDataProvider> p_mapDataProvider, QWidget *parent = 0);
    void addPixel(QPointF pixel);
    int getPixelsSize();
    QPointF getFirstPixel();
    QPointF getCurrentPixel();
    void setCurrentPixel(QPointF p_currentPixel);
    void drawTerrainProfile(RadioButtonType);
    ~TerrainProfile();
signals:
    void drawLine();

private:
    void drawTerrainProfile(QPixmap & pxMap, const std::vector<std::pair<int, int>> & vector);
    void drawSignal(QPixmap & pxMap, const std::vector<std::pair<int, int>> & vector);
    double findMinHeightFromVector(const std::vector<std::pair<int, int>> & vector);
    double findMaxHeightFromVector(const std::vector<std::pair<int, int>> & vector);
    double findValueFromData(std::pair<int, int> pixel);
    void saveInFile(const std::vector<std::pair<PixelXY, double>>& vector, std::string name);
    void saveInFileFromCorrectDraw(RadioButtonType);
    bool isPixelInLine(PixelXY pixel);

    Ui::TerrainProfile *ui;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * item;
    TerrainCanvas * canvas;
    std::vector<QPointF> pixels;
    QPointF currentPixel;
    std::shared_ptr<IMapDataProvider> mapDataProvider;
    const DataProvider & dataProvider;
    std::vector<std::pair<int, int>> vectorOfPiels;

    void displayImage(const QPixmap & img);
};

#endif // TERRAINPROFILE_H
