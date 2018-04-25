#include "ImagePainter.h"
#include <QPainter>
#include <QPixmap>

ImagePainter::ImagePainter(const Rsrp & p_rsrp, QWidget *parent) :
    QWidget(parent),
    rsrp(p_rsrp)
{
}

QPixmap ImagePainter::paintImage()
{
    QPixmap px;
    px.load(":/mapy/mapa");
    QPainter painter(&px);
    for(int i = 100; i < 200; i++)
    {
        painter.setPen(getColor(i - 100));
        painter.drawLine(i,100,i,200);
    }
    painter.end();

    return px;
}

void ImagePainter::makeScale()
{
    findMin();
    findMax();
}

double ImagePainter::findMax()
{
    auto biggest = std::max_element(rsrp.begin(), rsrp.end(),
        [](const std::pair<PixelXY,double> & l, const std::pair<PixelXY,double> & r){
            return l.second < r.second;
    });
    return biggest->second;
}

double ImagePainter::findMin()
{
    auto biggest = std::min_element(rsrp.begin(), rsrp.end(),
        [](const std::pair<PixelXY,double> & l, const std::pair<PixelXY,double> & r){
            return l.second < r.second;
    });
    return biggest->second;
}

const QColor ImagePainter::getColor(double L)
{
    int r, g, b;
    double d = 256.0/20.0;

    if( L < 0)
    { //nadfiolet
        r = g = b = 0;
    }
    else if( L < 20)
    {
        r = 255 - d * L;
        g = 0;
        b = 255;
    }
    else if( L < 40)
    {
        r = 0;
        g = d * (L - 20);
        b = 255;

    }
    else if( L < 60)
    {
        r = 0;
        g = 255;
        b = 255 - d * (L - 40);
    }
    else if( L < 80)
    {
        r = d * (L - 60);
        g = 255;
        b = 0;
    }
    else if( L < 100)
    {
        r = 255;
        g = 255 - d * (L - 80);
        b = 0;
    }
    else
    { //podczerwień
        r = g = b = 0;
    }
    return QColor(r, g, b);
}
