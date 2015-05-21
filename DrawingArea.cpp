#include "DrawingArea.h"

#include "mainwindow.h"
#include "textdialog.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QtWidgets>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include "Shapes.h"
#include "lineShape.h"
#include "rectangleShape.h"
#include "ellipseShape.h"
#include "eraserInstrument.h"
#include "pencilInstrument.h"
#include "textInstrument.h"
#include "selectInstrument.h"

#include <memory.h>

using namespace std;


int DrawingArea::selectedTool = 2;
QColor DrawingArea::myPenColor = Qt::blue;
int DrawingArea::myPenWidth = 1;
QString DrawingArea::text = "";


DrawingArea::DrawingArea(QWidget *parent) :
      QWidget(parent)
{
    mPix = QPixmap(QWidget::size());
    mPix.fill(Qt::white);

    //Default Shape drawn on startup is the Line Shape, so we have a Line Shape
    // pointer to myShape
    LINESHAPE *mL = new LINESHAPE;
    myShape = mL;


    //set everything to false as nothing has started yet
    mousePressed = false;
    drawStarted = false;
    undoVar = false;

}

DrawingArea::~DrawingArea()
{

}

//sets current tool to be used in the DrawingArea Widget
void DrawingArea::setDrawingObject(SHAPES *b){

    //myShape is a Shapes class pointer which stores the passed pointer
    //for later use
    myShape = b;

}

void DrawingArea::printShapes()
{

    undoVar = true;
    update();
}

//set the color of the Pen
void DrawingArea::setPenColor(const QColor &color)
{
    myPenColor = color;

}

//set the width of the Pen
void DrawingArea::setPenWidth(int w)
{
    myPenWidth = w;

}


//set the Text entered in the textDialog to the QString variable 'text' which is painted in the widget
void DrawingArea::setText(QString myText)
{
    text = myText;

}

//set the Selected tool to be used in the widget
void DrawingArea::setSelectedTool(int t)
{
    selectedTool = t;

}

//famous mousePressEvent
void DrawingArea::mousePressEvent(QMouseEvent* event)
{
    //Mouse is pressed for the first time
    mousePressed = true;

    /*Checking if the myShape object is the lineShape
    type then create a new object of that type, go through the same process for all other
    tools as well*/
    if(dynamic_cast<LINESHAPE*>(myShape))
    {
        myShape = new LINESHAPE;
    }
    else if(dynamic_cast<RECTANGLESHAPE*>(myShape))
    {
        myShape = new RECTANGLESHAPE;
    }
    else if(dynamic_cast<ELLIPSESHAPE*>(myShape))
    {
        myShape = new ELLIPSESHAPE;
    }
    else if(dynamic_cast<PENCILINSTRUMENT*>(myShape))
    {
        myShape = new PENCILINSTRUMENT;
    }
    else if(dynamic_cast<ERASERINSTRUMENT*>(myShape))
    {
        myShape = new ERASERINSTRUMENT;
    }
    else if(dynamic_cast<TEXTINSTRUMENT*>(myShape))
    {
        myShape = new TEXTINSTRUMENT;
    }

    //depending on Object type setPoint methods of
    //Different object is called
    myShape->setPoint1(event->pos());
    myShape->setPoint2(event->pos());

}

//famous mouseMoveEvent
void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{

    //As mouse is moving set the second point again and again
    // and update continuously
    if(event->type() == QEvent::MouseMove){
        myShape->setPoint2(event->pos());
    }

    //it calls the paintEvent() function continuously
    update();

 }

//famous mouseReleaseEvent
void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    //When mouse is released update for the one last time
    mousePressed = false;
    update();

}

//The popular paintEvent
void DrawingArea::paintEvent(QPaintEvent *event)
{

    painter.begin(this);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));


    //When the mouse is pressed
    if(mousePressed){
        // we are taking QPixmap reference again and again on mouse move and painting on the
        // widget again and again hence the painter view has a feeling of dynamic drawing

        painter.drawPixmap(0,0,mPix);

        /*Depending on the type of myShape object, the appropriate method is called for painting.
        The benefit is that we don't need to know Shape type beforehand */

        if(dynamic_cast<LINESHAPE*>(myShape)){
            painter.drawLine(dynamic_cast<LINESHAPE*>(myShape)->qline);
        }
        else if(dynamic_cast<RECTANGLESHAPE*>(myShape))
        {
            painter.drawRect(dynamic_cast<RECTANGLESHAPE*>(myShape)->qRect);
            //painter.drawPolyline(dynamic_cast<RECTANGLESHAPE*>(myShape)->qPoly);
        }
        else if(dynamic_cast<TEXTINSTRUMENT*>(myShape))
        {
            painter.setPen(QPen(myPenColor, myPenWidth, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            painter.setBackgroundMode(Qt::TransparentMode);
            //painter.drawRect(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect);
            //painter.drawText(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect, Qt::AlignCenter, "Great");
            //painter.drawText(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect, Qt::AlignCenter, text);
            painter.drawText(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect, Qt::AlignCenter, text);
        }
        else if(dynamic_cast<PENCILINSTRUMENT*>(myShape)){
           QPainter tPainter(&mPix);
           tPainter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
           tPainter.drawLine(dynamic_cast<PENCILINSTRUMENT*>(myShape)->qline.p1(), dynamic_cast<PENCILINSTRUMENT*>(myShape)->qline.p2());

           dynamic_cast<PENCILINSTRUMENT*>(myShape)->setPoint1(dynamic_cast<PENCILINSTRUMENT*>(myShape)->qline.p2());
        }
        else if(dynamic_cast<ELLIPSESHAPE*>(myShape))
        {
            painter.drawEllipse(dynamic_cast<ELLIPSESHAPE*>(myShape)->qEllipse);
        }
        else if(dynamic_cast<ERASERINSTRUMENT*>(myShape))
        {

           QPainter tPainter(&mPix);
           tPainter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
           tPainter.drawLine(dynamic_cast<ERASERINSTRUMENT*>(myShape)->qEraser.p1(), dynamic_cast<ERASERINSTRUMENT*>(myShape)->qEraser.p2());

           dynamic_cast<ERASERINSTRUMENT*>(myShape)->setPoint1(dynamic_cast<ERASERINSTRUMENT*>(myShape)->qEraser.p2());

        }
        else if(dynamic_cast<SELECTINSTRUMENT*>(myShape))
        {
            painter.setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawRect(dynamic_cast<SELECTINSTRUMENT*>(myShape)->qRect);
        }

        drawStarted = true;
        undoVar = false;
    }
    else if (drawStarted && !undoVar){
        // It created a QPainter object by taking  a reference
        // to the QPixmap object created earlier, then draws a line
        // using that object, then sets the earlier painter object
        // with the newly modified QPixmap object
        QPainter tempPainter(&mPix);
        tempPainter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        if(dynamic_cast<RECTANGLESHAPE*>(myShape))
        {
            tempPainter.drawRect(dynamic_cast<RECTANGLESHAPE*>(myShape)->qRect);
            //tempPainter.drawPolyline(dynamic_cast<RECTANGLESHAPE*>(myShape)->qPoly);
        }
        else if(dynamic_cast<LINESHAPE*>(myShape))
        {
            tempPainter.drawLine(dynamic_cast<LINESHAPE*>(myShape)->qline);
        }
        else if(dynamic_cast<TEXTINSTRUMENT*>(myShape))
        {
            tempPainter.setPen(QPen(myPenColor, myPenWidth, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            //tempPainter.drawRect(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect);
            //tempPainter.drawText(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect, Qt::AlignCenter, "Great");
            tempPainter.drawText(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect, Qt::AlignCenter, text);
        }
        else if(dynamic_cast<PENCILINSTRUMENT*>(myShape)){
            tempPainter.drawLine(dynamic_cast<PENCILINSTRUMENT*>(myShape)->qline);
        }
        else if(dynamic_cast<ELLIPSESHAPE*>(myShape)){
            tempPainter.drawEllipse(dynamic_cast<ELLIPSESHAPE*>(myShape)->qEllipse);
        }
        else if(dynamic_cast<SELECTINSTRUMENT*>(myShape))
        {
            tempPainter.setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            tempPainter.drawRect(dynamic_cast<SELECTINSTRUMENT*>(myShape)->qRect);
        }
        else if(dynamic_cast<ERASERINSTRUMENT*>(myShape)){
            tempPainter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            tempPainter.drawLine(dynamic_cast<ERASERINSTRUMENT*>(myShape)->qEraser);
        }

        //saving shapes in a vector
        myShapeVector.push_back((myShape));

        painter.drawPixmap(0,0,mPix);
        undoVar = false;
    }

    else if (undoVar){

        if(!myShapeVector.empty())
        {
        myShapeVector.pop_back();

        mPix.fill(Qt::white);
        QPainter tempPainter(&mPix);
        tempPainter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        unsigned int size = myShapeVector.size();
        qDebug() << size;
        for (unsigned int i = 0; i < size; i++)
        {
            if(dynamic_cast<RECTANGLESHAPE*>(myShapeVector[i]))
            {
                tempPainter.drawRect(dynamic_cast<RECTANGLESHAPE*>(myShapeVector[i])->qRect);
                //tempPainter.drawPolyline(dynamic_cast<RECTANGLESHAPE*>(myShapeVector[i])->qPoly);
            }
            else if(dynamic_cast<LINESHAPE*>(myShapeVector[i]))
            {
                tempPainter.drawLine(dynamic_cast<LINESHAPE*>(myShapeVector[i])->qline);
            }
            else if(dynamic_cast<ELLIPSESHAPE*>(myShapeVector[i])){
                tempPainter.drawEllipse(dynamic_cast<ELLIPSESHAPE*>(myShapeVector[i])->qEllipse);
            }
            else if(dynamic_cast<TEXTINSTRUMENT*>(myShapeVector[i]))
            {
                tempPainter.setPen(QPen(myPenColor, myPenWidth, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                //tempPainter.drawRect(dynamic_cast<TEXTINSTRUMENT*>(myShape)->qRect);
                //tempPainter.drawText(dynamic_cast<TEXTINSTRUMENT*>(myShapeVector[i])->qRect, Qt::AlignCenter, "Great");
                tempPainter.drawText(dynamic_cast<TEXTINSTRUMENT*>(myShapeVector[i])->qRect, Qt::AlignCenter, text);
            }
            else if(dynamic_cast<PENCILINSTRUMENT*>(myShapeVector[i]))
            {
                tempPainter.drawLine(dynamic_cast<PENCILINSTRUMENT*>(myShapeVector[i])->qline) ; //.p1(), dynamic_cast<MyPenShape*>(myShapeVector[i])->qline.p2());

            }
            else if(dynamic_cast<SELECTINSTRUMENT*>(myShapeVector[i]))
            {
                tempPainter.setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                tempPainter.drawRect(dynamic_cast<SELECTINSTRUMENT*>(myShapeVector[i])->qRect);
            }
            else if(dynamic_cast<ERASERINSTRUMENT*>(myShapeVector[i]))
            {
                tempPainter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                tempPainter.drawLine(dynamic_cast<ERASERINSTRUMENT*>(myShapeVector[i])->qEraser);
            }
        }
        painter.drawPixmap(0,0,mPix);
        }
    }

    painter.end();


}

bool DrawingArea::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Widget"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    mPix.load(fileName,0,Qt::AutoColor);

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

//    connect(document(), SIGNAL(contentsChanged()),
//            this, SLOT(documentWasModified()));

    return true;
}

void DrawingArea::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    //document()->setModified(false);
    setWindowModified(false);

    //setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

bool DrawingArea::saveImage(const QString &fileName, const char *fileFormat)
 {
    QImage visibleImage = mPix.toImage();// mPix instead of image;

    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat))  {
        modified = false;

        return true;
    } else  {
        return false;
    }
    //update();

}

void DrawingArea::resizeImage(QImage *image, const QSize &newSize)
{
    if(image->size() == newSize)
    return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;

    update();

}

bool DrawingArea::openImage(const QString &fileName)
{
    QImage loadedImage;

    if(!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

void DrawingArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}




