#include "lineShape.h"
#include <qdebug.h>

LINESHAPE::LINESHAPE()
{

}

void LINESHAPE::setPoint1(QPoint p1)
{
    qline.setP1(p1);
    //qDebug() << "point 1";

}

void LINESHAPE::setPoint2(QPoint p2)
{
    qline.setP2(p2);
    //qDebug() << "point 2";
}

void LINESHAPE::print()
{
    qDebug() << qline;
    //qDebug() << qline.p2();
}
