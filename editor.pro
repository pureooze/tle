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
    roomgui.cpp \
    prompterAddExit.cpp

HEADERS  += \
    editor.h \
    room.h \
    scene.h \
    roomgui.h \
    prompterAddExit.h

FORMS    += \
    editor.ui \
    prompterAddExit.ui
