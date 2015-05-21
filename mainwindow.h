#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QAction>
#include <QStatusBar>
#include <QTabWidget>
#include <QLabel>
#include <QUndoGroup>

#include "textdialog.h"
#include "DrawingArea.h"

QT_BEGIN_NAMESPACE

class ToolBar;
class PaletteBar;

QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DrawingArea *drawingArea;
    DrawingArea *createDrawingAreaChild();

    textDialog *textdialog;
    void penChanged();
    void initializeNewTab();
    bool openFile(const QString &fileName);


private slots:

    DrawingArea* activeWidget();

    void penColor();
    void about();
    void closeTab(int index);
    void save();
    void open();

    void on_rectangleButton_clicked();

    void on_lineButton_clicked();

    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_actionLine_triggered();

    void on_actionRectangle_triggered();

    void on_actionEllipse_triggered();

    void on_circleButton_clicked();

    void on_eraserButton_clicked();

    void on_actionEraser_triggered();

    void on_actionUndo_triggered();

    void on_action_Close_triggered();

    void on_action_Exit_triggered();

    void on_action_Save_triggered();

    void on_colorButton_clicked();

    void on_penWidthSpinBox_valueChanged(int arg1);

    void on_actionSave_As_triggered();

    void on_actionAbout_MyPaintEasy_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionPen_triggered();

    void on_pencilButton_clicked();

    void on_actionText_triggered();

    void on_textButton_clicked();

    void on_selectionButton_clicked();

    void on_actionSelection_triggered();

private:
    Ui::MainWindow *ui;

    bool saveFile(const QByteArray &fileFormat);
    bool maybeSave();


protected:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
