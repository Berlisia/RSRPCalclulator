#include "MouseEventTool.h"
#include <QEvent>
#include <iostream>

MouseEventTool::MouseEventTool()
{

}

void MouseEventTool::handleEvent(QEvent *event)
{
//    if (event->type() == QEvent::KeyPress)
//    {
//        QKeyEvent *ke = reinterpret_cast<QKeyEvent *>(event);
//        keyPress(ke);
//        return true;
//    }
//    else if (event->type() == QEvent::MouseButtonPress)
//    {
//        QMouseEvent *me = reinterpret_cast<QGraphicsSceneMouseEvent *>(event);
//        mousePress(me);
//    }
//    else if (event->type() == QEvent::MouseMove)
//    {
//        QMouseEvent *me = reinterpret_cast<QGraphicsSceneMouseEvent *>(event);
//        mouseMove(me);
//    }
//    else if (event->type() == QEvent::MouseButtonRelease)
//    {
//        QMouseEvent *me = reinterpret_cast<QGraphicsSceneMouseEvent *>(event);
//        mouseRelease(me);
//    }
    std::cout << "Dupa z handle Event" << std::endl;
}
