#include "ScribbleArea.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <cmath>
#include <iostream>

ScribbleArea::ScribbleArea(QCheckBox *p_checkBox, QCheckBox *p_TerrainCheckBox, std::vector<std::pair<PixelXY,double>> &p_data, QLabel *p_valueLabel,
                           const QPixmap & parent) :
    QGraphicsPixmapItem(parent),
    checkBox(p_checkBox),
    terrainCheckBox(p_TerrainCheckBox),
    data(p_data),
    valueLabel(p_valueLabel)
{
    setCacheMode(NoCache);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    valueLabel->show();
}

void ScribbleArea::setTerriainProfile(std::shared_ptr<TerrainProfile> p_terProfile)
{
    terProfile = std::move(p_terProfile);
}

void ScribbleArea::selectEvent(QGraphicsSceneMouseEvent *event)
{
    if(checkBox->isChecked())
    {
        findPossitionForValue(event);
    }
    else if(terrainCheckBox->isChecked())
    {
        choosePixelForTerrainProfile(event);
    }
}

double ScribbleArea::findFromData(PixelXY pixel)
{
    auto finded = std::find_if(data.begin(), data.end(),
                               [pixel](std::pair<PixelXY,double> px) -> bool {
                                     return px.first.getXy() == pixel.getXy();
    });
    return finded->second;
}

void ScribbleArea::choosePixelForTerrainProfile(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePosition = event->scenePos();
    //PixelXY px(static_cast<int>(mousePosition.rx()), static_cast<int>(mousePosition.ry()));
    terProfile->addPixel(mousePosition);
}

void ScribbleArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    selectEvent(event);
}

void ScribbleArea::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selectEvent(event);
}

void ScribbleArea::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(terrainCheckBox->isChecked())
    {
        if(terProfile->getPixelsSize() == 1)
        {
            terProfile->setCurrentPixel(event->scenePos());
            emit terProfile->drawLine();
        }
    }
}

void ScribbleArea::findPossitionForValue(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePosition = event->scenePos();
    PixelXY px(static_cast<int>(mousePosition.rx()), static_cast<int>(mousePosition.ry()));
    double value = findValueForPixel(px);
    setValueInLabel(value);
}

void ScribbleArea::setValueInLabel(double value)
{
    if(value == 0.000000)
    {
        valueLabel->setText("-");
    }
    else
    {
        valueLabel->setText(std::to_string(value).c_str());
    }
}

double ScribbleArea::findValueForPixel(PixelXY pixel)
{
    double value = 0.000000;
    if(!data.empty())
    {
        value = findFromData(pixel);
    }
    return value;
}

