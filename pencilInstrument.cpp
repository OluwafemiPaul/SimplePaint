#include "pencilInstrument.h"
#include <qdebug.h>

#include <QtWidgetsDepends>


PENCILINSTRUMENT::PENCILINSTRUMENT()
{
    //qline = new Qline;
}

void PENCILINSTRUMENT::setPoint1(QPoint p1)
{
    qline.setP1(p1);
    //qDebug() << "point 1";

}

void PENCILINSTRUMENT::setPoint2(QPoint p2)
{
    qline.setP2(p2);
    //qDebug() << "point 2";
}

void PENCILINSTRUMENT::print()
{
    qDebug() << qline;
    //qDebug() << qline.p2();
}
