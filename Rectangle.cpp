#include "Rectangle.h"

Rectangle::Rectangle()
{
    m_fillColor = QColor(50, 150, 0);
    m_lineColor = QColor(0,255,255);
    m_lineThickness = 5;

    m_position = QPoint(10, 10);
    m_width = 100;
    m_height = 50;
}

void Rectangle::draw(QPainter *painter)
{
    QBrush brush(m_fillColor);
    QPen pen(m_lineColor);

    if (m_lineThickness == 0) pen.setStyle(Qt::NoPen);

    pen.setWidth(m_lineThickness);

    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawRect(QRect(m_position.x(),
                            m_position.y(),
                            m_width, m_height));
    //painter->end();
}

QRect Rectangle::getBoundary()
{
    int margin = 4;
    return QRect(getPosition().x() - margin,
                 getPosition().y() - margin,
                 m_width  + margin*2 + 1,
                 m_height + margin*2 + 1);
}

bool Rectangle::contains(int x, int y)
{
    return QRect(getPosition().x(),
                 getPosition().y(),
                 m_width, m_height).contains(x, y);
}
int Rectangle::getWidth() const
{
    return m_width;
}

void Rectangle::setWidth(int value)
{
    m_width = value;
}
int Rectangle::getHeight() const
{
    return m_height;
}

void Rectangle::setHeight(int value)
{
    m_height = value;
}

void Rectangle::setPosition(const QPointF &pos)
{
    m_position = pos;
}

QPointF Rectangle::getPosition()
{
    return m_position;
}
