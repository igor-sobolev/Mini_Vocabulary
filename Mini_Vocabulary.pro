#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T21:34:33
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mini_Vocabulary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addwords.cpp \
    about.cpp \
    delete.cpp \
    testdialog.cpp \
    test.cpp \
    settings.cpp \
    aboutdb.cpp

HEADERS  += mainwindow.h \
    addwords.h \
    about.h \
    delete.h \
    testdialog.h \
    test.h \
    settings.h \
    aboutdb.h \
    selectedword.h

FORMS    += mainwindow.ui \
    addwords.ui \
    about.ui \
    delete.ui \
    testdialog.ui \
    test.ui \
    settings.ui \
    aboutdb.ui

RESOURCES += \
    resources.qrc

win32:RC_ICONS += app.ico
