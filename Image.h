#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPaintEvent>
#include <QColor>

class Image : public QWidget
{
public:
    Image(int sizeX, int sizeY);

    void paintPixel(QPoint & possition, QRgb color);
    void paintEvent(QPaintEvent*e);

    void setMaxValue(float max);
    void setMinValue(float min);
    void calculateFactor();
    QColor generateColor(float currentValue) const;

private:
    QImage img;

    struct Scale
    {
        float maxValue;
        float minValue;
        float factor;

        void calculateFactor()
        {
            factor = (maxValue-minValue)/360;
        }

        QColor rsrpToColor(float currentValue) const
        {
            int ci[3];
            float interval = maxValue - currentValue;
            if(interval < 0) interval = -interval;

            ci[0] = interval / factor;

            QColor color;
            color = color.toHsv();
            color.setHsv(ci[0], 0, 1);
            return color;
        }
    }scale;
};

#endif // IMAGE_H
