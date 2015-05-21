#include "rectangleShape.h"
#include "qdebug.h"

RECTANGLESHAPE::RECTANGLESHAPE()
{
}


void RECTANGLESHAPE::setPoint1(QPoint p1)
{
    qRect.setTopLeft(p1);
    //qPoly.setPoint(p1);
    //qDebug() << "rect 1";
}

void RECTANGLESHAPE::setPoint2(QPoint p2)
{
    qRect.setBottomRight(p2);
    //qPoly.setPoint(p2);
    //qDebug() << "rect 1";
}
