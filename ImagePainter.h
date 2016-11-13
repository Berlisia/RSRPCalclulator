#ifndef IMAGEPAINTER_H
#define IMAGEPAINTER_H
#include <QWidget>
#include "Core/PixelXY.h"

typedef std::vector<std::pair<PixelXY,float>> Rsrp;

class QPainter;
class ImagePainter : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePainter(const Rsrp & p_rsrp, QWidget *parent = 0);

    const QPixmap& paintImage();
    const QColor getColor(float L);
    float findMax();
    float findMin();

signals:

public slots:

private:
    void makeScale();

    const Rsrp & rsrp;
};

#endif // IMAGEPAINTER_H
