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

    void setMaxValue(double max);
    void setMinValue(double min);
    void calculateFactor();
    QColor generateColor(double currentValue) const;

private:
    QImage img;

    struct Scale
    {
        double maxValue;
        double minValue;
        double factor;

        void calculateFactor()
        {
            factor = (maxValue-minValue)/360;
        }

        QColor rsrpToColor(double currentValue) const
        {
            int ci[3];
            double interval = maxValue - currentValue;
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
