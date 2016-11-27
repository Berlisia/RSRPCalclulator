#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QPoint>
#include <QColor>
#include <QRect>
#include <QBrush>
#include <QPainter>

class Rectangle
{
public:
    Rectangle();

    void draw(QPainter *painter);
    QRect getBoundary();
    bool contains(int x, int y);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    void setPosition(const QPointF &pos);
    QPointF getPosition();

private:
    QPointF m_position;
    QColor m_fillColor;
    QColor m_lineColor;
    int m_lineThickness;
    int m_width;
    int m_height;
};

#endif // RECTANGLE_H
