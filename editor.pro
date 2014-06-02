#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T02:14:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = editor
TEMPLATE = app


SOURCES += \
    editor.cpp \
    main.cpp \
    room.cpp \
    scene.cpp \
    prompterAddExit.cpp \
    events.cpp \
    object.cpp \
    addobjectdialog.cpp

HEADERS  += \
    editor.h \
    room.h \
    scene.h \
    prompterAddExit.h \
    events.h \
    object.h \
    addobjectdialog.h

FORMS    += \
    editor.ui \
    prompterAddExit.ui \
    addobjectdialog.ui

RESOURCES += \
    img/icons.qrc
