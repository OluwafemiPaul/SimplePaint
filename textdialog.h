#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include "DrawingArea.h"
#include <QDialog>
#include <QFont>

namespace Ui {
class textDialog;
}

class textDialog : public QDialog
{
    Q_OBJECT

public:
    explicit textDialog(QWidget *parent = 0);
    ~textDialog();

    DrawingArea *drawingArea;

    void textInput();
    void setFont();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    //void on_fontButton_clicked();

private:
    Ui::textDialog *ui;

    QString tempText, text;
    QFont font;
};

#endif // TEXTDIALOG_H
