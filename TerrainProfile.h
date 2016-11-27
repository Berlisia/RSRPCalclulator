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
    ~TerrainProfile();
signals:
    void drawLine();

public slots:
    void drawTerrainProfile();

private:
    void drawTerrainProfile(QPixmap & pxMap, const std::vector<std::pair<int, int>> & vector);
    void drawSignal(QPixmap & pxMap, const std::vector<std::pair<int, int>> & vector);
    float findMinHeightFromVector(const std::vector<std::pair<int, int>> & vector);
    float findMaxHeightFromVector(const std::vector<std::pair<int, int>> & vector);
    float findValueFromData(std::pair<int, int> pixel);

    Ui::TerrainProfile *ui;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * item;
    TerrainCanvas * canvas;
    std::vector<QPointF> pixels;
    QPointF currentPixel;
    std::shared_ptr<IMapDataProvider> mapDataProvider;
    const DataProvider & dataProvider;

    void displayImage(const QPixmap & img);
};

#endif // TERRAINPROFILE_H
