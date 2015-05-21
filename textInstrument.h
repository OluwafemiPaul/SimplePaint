#ifndef TEXTINSTRUMENT_H
#define TEXTINSTRUMENT_H

#include "Shapes.h"

#include <QRect>

class TEXTINSTRUMENT : public SHAPES
{
public:
    QRect qRect;
    QString mText;
    TEXTINSTRUMENT();
    void setPoint1(QPoint p1);
    void setPoint2(QPoint p2);
    void print();
};

#endif // TEXTINSTRUMENT_H
