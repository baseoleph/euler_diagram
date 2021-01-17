# Euler Diagram
# Copyright (C) 2020 baseoleph@gmail.com

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    filledpath.cpp \
    main.cpp \
    mainwindow.cpp \
    scene.cpp

HEADERS += \
    filledpath.h \
    mainwindow.h \
    scene.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
