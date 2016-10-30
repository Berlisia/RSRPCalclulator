#include "Image.h"

Image::Image(int sizeX, int sizeY) : QWidget(),
    img(sizeX, sizeY, QImage::Format_RGB32)
{
    setFixedSize(sizeX, sizeY);
}

void Image::paintPixel(QPoint &possition, QRgb color)
{
    img.setPixel(possition, color);
}

void Image::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e);

    QPainter paint(this);
    paint.drawImage(0,0, img);
}

void Image::setMaxValue(float max)
{
    scale.maxValue = max;
}

void Image::setMinValue(float min)
{
    scale.minValue = min;
}

void Image::calculateFactor()
{
    scale.calculateFactor();
}

QColor Image::generateColor(float currentValue) const
{
    return scale.rsrpToColor(currentValue);
}
