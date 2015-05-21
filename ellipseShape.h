#ifndef ELLIPSESHAPE_H
#define ELLIPSESHAPE_H

#include "Shapes.h"
#include <QRect>


class ELLIPSESHAPE : public SHAPES
{
public:
    QRect qEllipse;
    ELLIPSESHAPE();
    void setPoint1(QPoint p1);
    void setPoint2(QPoint p2);
};

#endif // ELLIPSESHAPE_H
