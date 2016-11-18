#include "ScribbleArea.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <cmath>
#include <iostream>

ScribbleArea::ScribbleArea(QCheckBox *p_checkBox, DataProvider &p_data, QLabel *p_valueLabel,
                           const QPixmap & parent) :
    QGraphicsPixmapItem(parent),
    checkBox(p_checkBox),
    data(p_data),
    valueLabel(p_valueLabel)
{
    setCacheMode(NoCache);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    valueLabel->show();
}

void ScribbleArea::selectEvent(QGraphicsSceneMouseEvent *event)
{
    if(checkBox->isChecked())
    {
        findPossitionForValue(event);
    }
}

float ScribbleArea::findFromData(PixelXY pixel)
{
    auto finded = std::find_if(data.rsrp.vector.begin(), data.rsrp.vector.end(),
                               [pixel](std::pair<PixelXY,float> px) -> bool {
                                     return px.first.getXy() == pixel.getXy();
    });
    return finded->second;
}

void ScribbleArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    selectEvent(event);
}

void ScribbleArea::findPossitionForValue(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePosition = event->scenePos();
    PixelXY px(static_cast<int>(mousePosition.rx()), static_cast<int>(mousePosition.ry()));
    float value = findValueForPixel(px);
    setValueInLabel(value);
}

void ScribbleArea::setValueInLabel(float value)
{
    if(value == 0.000000)
    {
        valueLabel->setText("-");
    }
    else valueLabel->setText(std::to_string(value).c_str());
}

float ScribbleArea::findValueForPixel(PixelXY pixel)
{
    float value = 0.000000;
    if(!data.rsrp.vector.empty())
    {
        value = findFromData(pixel);
    }
    return value;
}

