QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CELL_LAUNCH

TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Sources/DropShadowDialog.cpp \
    Sources/DropShadowWidget.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/guidedialog.cpp \
    Sources/homepagewidget.cpp \
    Sources/settingspagewidget.cpp


HEADERS += \
    Headers/DropShadowDialog.h \
    Headers/DropShadowWidget.h \
    Headers/_utility.h \
    Headers/mainwindow.h \
    Headers/guidedialog.h \
    Headers/qstylesheetloader.h \
    Headers/homepagewidget.h \
    Headers/settingspagewidget.h

win32{
SOURCES += \
    Sources/WindWMAPI.cpp

HEADERS += \
    Headers/WindWMAPI.h
}

FORMS += \
    Forms/mainwindow.ui \
    Forms/guidedialog.ui \
    Forms/homepagewidget.ui \
    Forms/settingspagewidget.ui

LIBS += C:\Users\HengyiYu\Desktop\Projects\c++\Qt\Cell_DeepLearning\Share\libs\QStyleSheetLoader.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc

RC_ICONS = CELL.ico
