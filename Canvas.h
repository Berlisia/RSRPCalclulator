#ifndef CANVAS_H
#define CANVAS_H
#include <QWidget>
#include <QGraphicsObject>
#include "Rectangle.h"
#include "DrawRectangle.h"


class Canvas : public QGraphicsPixmapItem
{
public:
    Canvas(const QPixmap & parent);

    void setTool(DrawRectangle * p_tool);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

private:
    DrawRectangle * tool;
};

#endif // CANVAS_H
