#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include "Shapes.h"
#include "lineShape.h"

#include <QWidget>

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QMouseEvent>
#include <QPoint>

class DrawingArea : public QWidget
{
    Q_OBJECT

public:

    explicit DrawingArea(QWidget *parent = 0);
    ~DrawingArea();

    //Creating a vector to store the shapes
    vector<SHAPES*> myShapeVector;

    void setDrawingObject(SHAPES *b);
    SHAPES *myShape;

    void printShapes();
    void setPenColor(const QColor &color);
    void setPenWidth(int w);
    void setText(QString myText);
    QColor penColor() const {return myPenColor;}
    int penWidth() const {return myPenWidth;}

    bool loadFile(const QString &fileName);
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    bool isModified() const  { return modified; }

    void setCurrentFile(const QString &fileName);

    inline QString getFileName() { return (mFilePath.isEmpty() ? mFilePath :
                                           mFilePath.split('/').last()); }



public slots:

    void setSelectedTool(int t);


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);



private:

    QPainter painter;

    static QColor myPenColor;
    static int myPenWidth;
    static QString text;
    static int selectedTool;

    bool modified;
    bool isUntitled;

    bool mousePressed;
    bool drawStarted;
    bool undoVar;

    QImage image;
    QPixmap mPix;
    QString curFile;
    QString mFilePath;

    void resizeImage(QImage *image, const QSize &newSize);


signals:


};

#endif // DRAWINGAREA_H
