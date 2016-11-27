#include "Canvas.h"
#include <memory>
#include <QMouseEvent>

Canvas::Canvas(const QPixmap &parent) :  QGraphicsPixmapItem(parent)
{
}

void Canvas::setTool(DrawRectangle *p_tool)
{
    tool = p_tool;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    tool->mousePress(event);
    //tool->draw();
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    tool->mouseMove(event);
    tool->draw();
}
