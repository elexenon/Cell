QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CELL_LAUNCH

TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp \


HEADERS += \
    Headers/_utility.h \
    Headers/mainwindow.h \

win32{
SOURCES += \
    Sources/WindWMAPI.cpp

HEADERS += \
    Headers/WindWMAPI.h
}

FORMS += \
    Forms\mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc

RC_ICONS = CELL.ico
