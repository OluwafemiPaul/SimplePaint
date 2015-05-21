#include "ellipseShape.h"

ELLIPSESHAPE::ELLIPSESHAPE()
{
}

void ELLIPSESHAPE::setPoint1(QPoint p1)
{
    qEllipse.setTopLeft(p1);
}

void ELLIPSESHAPE::setPoint2(QPoint p2)
{
    qEllipse.setBottomRight(p2);
}

