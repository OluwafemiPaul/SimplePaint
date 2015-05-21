#ifndef ERASERINSTRUMENT_H
#define ERASERINSTRUMENT_H

#include "Shapes.h"

#include <QtWidgetsDepends>

class ERASERINSTRUMENT : public SHAPES
{
public:
    QLine qEraser;
    ERASERINSTRUMENT();
    void setPoint1(QPoint p1);
    void setPoint2(QPoint p2);
    void print();
};

#endif // ERASERINSTRUMENT_H
