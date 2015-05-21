#include "eraserInstrument.h"
#include <qdebug.h>

ERASERINSTRUMENT::ERASERINSTRUMENT()
{

}

void ERASERINSTRUMENT::setPoint1(QPoint p1)
{
    qEraser.setP1(p1);
    //qDebug() << "point 1";

}

void ERASERINSTRUMENT::setPoint2(QPoint p2)
{
    qEraser.setP2(p2);
    //qDebug() << "point 2";
}

void ERASERINSTRUMENT::print()
{
    qDebug() << qEraser;
    //qDebug() << qline.p2();
}
