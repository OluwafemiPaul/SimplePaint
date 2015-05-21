#ifndef LINESHAPE_H
#define LINESHAPE_H

#include "Shapes.h"

#include <QtWidgetsDepends>

class LINESHAPE : public SHAPES
{
public:
    QLine qline;
    LINESHAPE();
    void setPoint1(QPoint p1);
    void setPoint2(QPoint p2);
    void print();
};


#endif // LINESHAPE_H
