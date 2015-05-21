#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include "Shapes.h"

#include <QRect>
#include <QPolygon>

class RECTANGLESHAPE : public SHAPES
{
public:
    QRect qRect;
    //QPolygon qPoly;

    RECTANGLESHAPE();
    void setPoint1(QPoint p1);
    void setPoint2(QPoint p2);
};


#endif // RECTANGLESHAPE_H
