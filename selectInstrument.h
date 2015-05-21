#ifndef SELECTINSTRUMENT_H
#define SELECTINSTRUMENT_H

#include "Shapes.h"

#include <QRect>

class SELECTINSTRUMENT : public SHAPES
{
public:
    QRect qRect;
    SELECTINSTRUMENT();
    void setPoint1(QPoint p1);
    void setPoint2(QPoint p2);
};


#endif // SELECTINSTRUMENT_H
