#include "DrawRectangle.h"
#include <QGraphicsSceneMouseEvent>

void DrawRectangle::mousePress(QGraphicsSceneMouseEvent* event)
{
    if(rectangle)
    {
        delete rectangle;
    }
    clickPressed = true;
    startPosition = event->scenePos();

    rectangle = new Rectangle();
    rectangle->setPosition(startPosition);

    rectangle->setWidth(2);
    rectangle->setHeight(2);
}

void DrawRectangle::mouseMove(QGraphicsSceneMouseEvent* event)
{
    if (clickPressed)
    {
        int distX = event->scenePos().x() - startPosition.x();
        int distY = event->scenePos().y() - startPosition.y();

        if (distX < 0)
        {
            rectangle->setPosition(QPoint(event->scenePos().x(), rectangle->getPosition().y()));
        }
        else
        {
            rectangle->setPosition(QPoint(startPosition.x(), rectangle->getPosition().y()));
        }

        if (distY < 0)
        {
            rectangle->setPosition(QPoint(rectangle->getPosition().x(), event->scenePos().y()));
        }
        else
        {
            rectangle->setPosition(QPoint(rectangle->getPosition().x(), startPosition.y()));
        }

        rectangle->setWidth(std::abs(distX));
        rectangle->setHeight(std::abs(distY));
    }
}

void DrawRectangle::mouseRelease(QGraphicsSceneMouseEvent* /*event*/)
{
    clickPressed = false;
}

void DrawRectangle::setRectangle(Rectangle* rect)
{
    rectangle = rect;
}

void DrawRectangle::setPainter(QPainter* p_painter)
{
    painter = p_painter;
}

void DrawRectangle::draw()
{
    rectangle->draw(painter);
    emit drawingDone();
}

Rectangle* DrawRectangle::getRect()
{
    return rectangle;
}

DrawRectangle::~DrawRectangle()
{
    delete rectangle;
}
