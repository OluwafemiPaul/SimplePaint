#include "textdialog.h"
#include "ui_textdialog.h"
#include "DrawingArea.h"

#include <QMessageBox>
#include <QFontDialog>

textDialog::textDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::textDialog)
{
    ui->setupUi(this);

    drawingArea = new DrawingArea();

    setWindowTitle(tr("Text Dialog"));
}

textDialog::~textDialog()
{
    delete ui;
}

void textDialog::textInput()
{
    text = tempText;
    //QMessageBox::information(this, tr("Message"), text);
}


void textDialog::on_okButton_clicked()
{
    tempText = ui->textEdit->toPlainText();
    //QMessageBox::information(this, tr("Message"), text);

    drawingArea->setText(tempText);
    //close();
}

void textDialog::on_cancelButton_clicked()
{
    ui->textEdit->clear();
    close();
}

//void textDialog::on_fontButton_clicked()
//{

//}
