#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H
#include "Core/PixelXY.h"
#include "DataProvider.h"
#include <QGraphicsObject>
#include <QCheckBox>
#include "TerrainProfile.h"

#include <QWidget>

class QGraphicsPixmapItem;
class QLabel;
class QGraphicsSceneMouseEvent;

class ScribbleArea : public QGraphicsPixmapItem
{

public:
    ScribbleArea(QCheckBox * p_checkBox, QCheckBox *p_TerrainCheckBox,
                 DataProvider & p_data,
                 QLabel * p_valueLabel,
                 const QPixmap &parent);

    void setTerriainProfile(std::shared_ptr<TerrainProfile> p_terProfile);

protected:
    void selectEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void findPossitionForValue(QGraphicsSceneMouseEvent *event);
    void setValueInLabel(float value);
    float findValueForPixel(PixelXY pixel);
    float findFromData(PixelXY pixel);
    void choosePixelForTerrainProfile(QGraphicsSceneMouseEvent *event);

    QCheckBox * checkBox;
    QCheckBox * terrainCheckBox;
    DataProvider & data;
    QLabel * valueLabel;
    std::shared_ptr<TerrainProfile> terProfile;
};

#endif // SCRIBBLEAREA_H
