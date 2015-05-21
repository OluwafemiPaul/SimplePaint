#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DrawingArea.h"

#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QFileDialog>
#include <QComboBox>
#include <QtWidgets>
#include <QColor>
#include "Shapes.h"
#include "lineShape.h"
#include "rectangleShape.h"
#include "ellipseShape.h"
#include "eraserInstrument.h"
#include "pencilInstrument.h"
#include "textInstrument.h"
#include "selectInstrument.h"
#include <QDebug>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawingArea = new DrawingArea();

    setWindowTitle(tr("Simple Paint"));

    setCursor(Qt::ArrowCursor);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeNewTab()
{

    ui->tabWidget->addTab(drawingArea, "newName");
}


void MainWindow::penChanged()
{
    int width = ui->penWidthSpinBox->value();
    drawingArea->setPenWidth(width);

}


void MainWindow::penColor()
 {
    QColor newColor = QColorDialog::getColor(drawingArea->penColor());
    if (newColor.isValid())
         drawingArea->setPenColor(newColor);
}


bool MainWindow::openFile(const QString &fileName)
{
    DrawingArea *draw = createDrawingAreaChild();
    const bool succeeded = draw->loadFile(fileName);
    if (succeeded) {
        draw->show();
        drawingArea->setSelectedTool(0);
    }
    else
        draw->close();
    return succeeded;
}

DrawingArea *MainWindow::createDrawingAreaChild(){

    DrawingArea *draw = new DrawingArea;
    ui->tabWidget->addTab(draw, "newTab");


    return draw;
}

DrawingArea *MainWindow::activeWidget()
{
    if (QWidget *activeWidget = ui->tabWidget->currentWidget())
        return qobject_cast<DrawingArea *>(activeWidget);

    //returns 0 if no casting possible
    return 0;
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    fileFormat = "png";
    saveFile(fileFormat);
}

void MainWindow::open()
{
    //if(maybeSave()) {
        //QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        QString fileName = QFileDialog::getOpenFileName(this);

        //if (!fileName.isEmpty()) {
        //    drawingArea->openImage(fileName);

        if (openFile(fileName))
            statusBar()->showMessage(tr("File loaded"), 2000);
        //}
    //}
}


bool MainWindow::saveFile(const QByteArray &fileFormat)
 {
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString(fileFormat.toUpper()))
                               .arg(QString(fileFormat)));
    if (fileName.isEmpty())  {
        return false;
    } else  {
        return drawingArea->saveImage(fileName, fileFormat);
    }
}

bool MainWindow::maybeSave()
 {
    if (drawingArea->isModified())  {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)  {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel)  {
            return false;
        }
    }
    return true;
}

void MainWindow::closeTab(int index)
{

    if (maybeSave())  {
        //event->accept();
    }
    else {

        QWidget *wid = ui->tabWidget->widget(index);
        ui->tabWidget->removeTab(index);
        delete wid;
        if (ui->tabWidget->count() == 0)
        {
            setWindowTitle("Empty - MyPaintEasy");
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
    if (maybeSave())  {
        event->accept();
    } else  {
        event->ignore();
    }
}


void MainWindow::about()
 {
    QMessageBox::about(this, tr("About SimplePaint"),
            tr("<p>The <b>SimplePaint</b> is a Paint Application "
               "for creating and editing Images. "
               "With Simple Paint, you can draw shapes with different Pen Sizes and Colors. "
               "You can also add text to your image and scribble just like you write with a pen."
               "</p><p> The App demonstrates "
               "how to use QPainter to draw an image in real time, as well as "
               "to repaint widgets. The App was developed in Qt using C++.</p>"
               "</p><p> <li><a href=\"mailto:oluwafemi.paul.olaleye@gmail.com\">Olaleye Oluwafemi Paul</a>"
               "(oluwafemi.paul.olaleye@gmail.com)</li>"
               "<br>Copyright (c) 2015 SimplePaint</p>"));
}




void MainWindow::on_lineButton_clicked()
{
    on_actionLine_triggered();

}

void MainWindow::on_actionLine_triggered()
{

    setCursor(Qt::ArrowCursor);

    if(!activeWidget()) return;
    DrawingArea *drawingWidget = activeWidget();

    //Creating a MyLineShape pointer for later use
    LINESHAPE *b = new LINESHAPE;

    //Polymorphic usage through reference
    drawingWidget->setDrawingObject(b);
    drawingArea = drawingWidget;
}

void MainWindow::on_actionRectangle_triggered()
{
    setCursor(Qt::CrossCursor);

    if(!activeWidget()) return;
    DrawingArea *drawingWidget = activeWidget();

    //Creating a RectangleShape pointer for later use
    RECTANGLESHAPE *r = new RECTANGLESHAPE;

    //Polymorphic usage through reference
    drawingWidget->setDrawingObject(r);
    drawingArea = drawingWidget;

}

void MainWindow::on_rectangleButton_clicked()
{
    on_actionRectangle_triggered();
}


void MainWindow::on_actionEllipse_triggered()
{
    setCursor(Qt::CrossCursor);

    if(!activeWidget()) return;
    DrawingArea *drawingWidget = activeWidget();

    //Creating a MyLineShape pointer for later use
    ELLIPSESHAPE *e = new ELLIPSESHAPE;

    //Polymorphic usage through reference
    drawingWidget->setDrawingObject(e);
    drawingArea = drawingWidget;

}

void MainWindow::on_circleButton_clicked()
{
    on_actionEllipse_triggered();
}

void MainWindow::on_actionPen_triggered()
{
    setCursor(Qt::PointingHandCursor);

    if(!activeWidget()) return;
    DrawingArea *drawingWidget = activeWidget();

    //Creating a MyLineShape pointer for later use
    PENCILINSTRUMENT *p = new PENCILINSTRUMENT;

    //Polymorphic usage through reference
    drawingWidget->setDrawingObject(p);
    drawingArea = drawingWidget;
}

void MainWindow::on_pencilButton_clicked()
{
    on_actionPen_triggered();
}

void MainWindow::on_actionText_triggered()
{
    setCursor(Qt::IBeamCursor);

    textdialog = new textDialog(this);
    textdialog->show();

    if(!activeWidget()) return;

    else {
        DrawingArea *drawingWidget = activeWidget();

        //Creating a MyLineShape pointer for later use
        TEXTINSTRUMENT *t = new TEXTINSTRUMENT;

        //Polymorphic usage through reference
        drawingWidget->setDrawingObject(t);
        drawingArea = drawingWidget;

        //textdialog = new textDialog(this);
        //textdialog->show();
    }

}

void MainWindow::on_textButton_clicked()
{
    on_actionText_triggered();
}


void MainWindow::on_eraserButton_clicked()
{

    on_actionEraser_triggered();
}

void MainWindow::on_actionEraser_triggered()
{
    //drawingArea->setSelectedTool(4);

    setCursor(Qt::OpenHandCursor);

    if(!activeWidget()) return;
    DrawingArea *drawingWidget = activeWidget();

    //Creating a MyLineShape pointer for later use
    ERASERINSTRUMENT *e = new ERASERINSTRUMENT;

    //Polymorphic usage through reference
    drawingWidget->setDrawingObject(e);
    drawingArea = drawingWidget;

}

void MainWindow::on_selectionButton_clicked()
{
    on_actionSelection_triggered();
}

void MainWindow::on_actionSelection_triggered()
{
    setCursor(Qt::ArrowCursor);

    if(!activeWidget()) return;
    DrawingArea *drawingWidget = activeWidget();

    //Creating a MyLineShape pointer for later use
    SELECTINSTRUMENT *s = new SELECTINSTRUMENT;

    //Polymorphic usage through reference
    drawingWidget->setDrawingObject(s);
    drawingArea = drawingWidget;
}

void MainWindow::on_colorButton_clicked()
{
    penColor();
}

void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    drawingArea->setPenWidth(arg1);

}


void MainWindow::on_action_New_triggered()
{
    //initializeNewTab();

    createDrawingAreaChild();
}

void MainWindow::on_action_Open_triggered()
{
    open();
}

void MainWindow::on_actionUndo_triggered()
{
    if(!activeWidget()) return;
    DrawingArea *drawingWidget = activeWidget();

    //Polymorphic usage through reference
    drawingWidget->printShapes();
}

void MainWindow::on_action_Close_triggered()
{
    //DrawingArea *drawingWidget = activeWidget();
    //drawingWidget->close();

    //int ind = ui->tabWidget->currentIndex();
    //ui->tabWidget->removeTab(ind);

    closeTab(ui->tabWidget->currentIndex());
}

void MainWindow::on_action_Exit_triggered()
{
    close();
    //closeEvent();
}

void MainWindow::on_action_Save_triggered()
{
    save();
}

void MainWindow::on_actionSave_As_triggered()
{ 
    save();
}

void MainWindow::on_actionAbout_MyPaintEasy_triggered()
{
    about();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}




