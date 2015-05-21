#include "selectInstrument.h"
#include "qdebug.h"

SELECTINSTRUMENT::SELECTINSTRUMENT()
{
}


void SELECTINSTRUMENT::setPoint1(QPoint p1)
{
    qRect.setTopLeft(p1);
    //qDebug() << "rect 1";
}

void SELECTINSTRUMENT::setPoint2(QPoint p2)
{
    qRect.setBottomRight(p2);
    //qDebug() << "rect 1";
}

