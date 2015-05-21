#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T11:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplePaint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DrawingArea.cpp \
    ellipseShape.cpp \
    eraserInstrument.cpp \
    lineShape.cpp \
    pencilInstrument.cpp \
    rectangleShape.cpp \
    selectInstrument.cpp \
    Shapes.cpp \
    textdialog.cpp \
    textInstrument.cpp

HEADERS  += mainwindow.h \
    DrawingArea.h \
    ellipseShape.h \
    eraserInstrument.h \
    lineShape.h \
    pencilInstrument.h \
    rectangleShape.h \
    selectInstrument.h \
    Shapes.h \
    textdialog.h \
    textInstrument.h

FORMS    += mainwindow.ui \
    textdialog.ui

RESOURCES += \
    my_paint.qrc
