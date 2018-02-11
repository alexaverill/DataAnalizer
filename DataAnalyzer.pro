#-------------------------------------------------
#
# Project created by QtCreator 2018-01-25T18:10:49
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QTPLUGIN += qsqlmysql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataAnalyzer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    data.cpp \
    database.cpp

HEADERS += \
        mainwindow.h \
    data.h \
    database.h \
    datapoint.h

FORMS += \
        mainwindow.ui
INCLUDEPATH += /usr/include/mysql \
            /home/aaverill/Qt/5.10.0/gcc_64/plugins/sqldrivers/