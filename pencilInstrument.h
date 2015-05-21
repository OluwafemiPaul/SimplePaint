#ifndef PENCILINSTRUMENT_H
#define PENCILINSTRUMENT_H

#include "Shapes.h"
#include <QtWidgetsDepends>

#include <QRect>

class PENCILINSTRUMENT : public SHAPES
{
public:
    QLine qline;
    PENCILINSTRUMENT();
    void setPoint1(QPoint p1);
    void setPoint2(QPoint p2);
    void print();
};

#endif // PENCILINSTRUMENT_H
