#ifndef MOUSEEVENTTOOL_H
#define MOUSEEVENTTOOL_H
class QEvent;
class QMouseEvent;
class QKeyEvent;
class QGraphicsSceneMouseEvent;

class MouseEventTool
{
public:
    MouseEventTool();

    void handleEvent(QEvent * event);

protected:
    virtual void mousePress(QGraphicsSceneMouseEvent*) {}
    virtual void mouseMove(QGraphicsSceneMouseEvent*) {}
    virtual void mouseRelease(QGraphicsSceneMouseEvent*) {}
    virtual void keyPress(QKeyEvent*) {}
};

#endif // MOUSEEVENTTOOL_H
