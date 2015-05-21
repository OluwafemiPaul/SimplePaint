#ifndef SHAPES_H
#define SHAPES_H

#include <QColor>
#include <QPoint>
#include <iostream>

using namespace std;

class SHAPES
{
public:
    SHAPES();
    QPoint p1;
    QPoint p2;

    QColor myPenColor;
    int myPenWidth;

    virtual void setPoint1(QPoint p1) {cout << "Shape::1 \n";};
    virtual void setPoint2(QPoint p2) {cout << "Shapre::2 \n";};
};




#endif // SHAPES_H
