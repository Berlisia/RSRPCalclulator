#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H
#include "Core/PixelXY.h"
#include "DataProvider.h"
#include <QGraphicsObject>
#include <QCheckBox>

#include <QWidget>

class QGraphicsPixmapItem;
class QLabel;
class QGraphicsSceneMouseEvent;

class ScribbleArea : public QGraphicsPixmapItem
{

public:
    ScribbleArea(QCheckBox * p_checkBox,
                 DataProvider & p_data,
                 QLabel * p_valueLabel,
                 const QPixmap &parent);
protected:
    void selectEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void findPossitionForValue(QGraphicsSceneMouseEvent *event);
    void setValueInLabel(float value);
    float findValueForPixel(PixelXY pixel);
    float findFromData(PixelXY pixel);

    QCheckBox * checkBox;
    DataProvider & data;
    QLabel * valueLabel;
};

#endif // SCRIBBLEAREA_H
