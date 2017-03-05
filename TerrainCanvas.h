#ifndef TERRAINCANVAS_H
#define TERRAINCANVAS_H
#include <QGraphicsObject>

class TerrainCanvas : public QGraphicsPixmapItem
{
public:
    TerrainCanvas(const QPixmap & parent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
};

#endif // TERRAINCANVAS_H
