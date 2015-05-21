#include "textInstrument.h"
#include <qdebug.h>

TEXTINSTRUMENT::TEXTINSTRUMENT()
{
    mText = QString();
}

void TEXTINSTRUMENT::setPoint1(QPoint p1)
{
    qRect.setTopLeft(p1);
    //qDebug() << "point 1";

}

void TEXTINSTRUMENT::setPoint2(QPoint p2)
{
    qRect.setBottomRight(p2);
    //qDebug() << "point 2";
}

void TEXTINSTRUMENT::print()
{
    //qDebug() << qline;
    //qDebug() << qline.p2();
}
