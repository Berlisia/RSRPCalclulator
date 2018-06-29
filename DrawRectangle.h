#ifndef DRAWRECTANGLE_H
#define DRAWRECTANGLE_H
#include "Rectangle.h"
#include <QGraphicsSceneMouseEvent>

class DrawRectangle : public QObject
{
    Q_OBJECT

public:
    void mousePress(QGraphicsSceneMouseEvent* event);
    void mouseMove(QGraphicsSceneMouseEvent* event);
    void mouseRelease(QGraphicsSceneMouseEvent* event);

    void setRectangle(Rectangle* rect);
    void setPainter(QPainter* p_painter);
    void draw();
    Rectangle* getRect();
    ~DrawRectangle();

signals:
    void drawingDone();

private:
    Rectangle* rectangle;
    bool clickPressed;
    QPointF startPosition;
    QPainter* painter;
};

#endif // DRAWRECTANGLE_H
