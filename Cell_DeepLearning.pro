QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CELL_LAUNCH

TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Sources/Kits/DropShadowDialog.cpp \
    Sources/Kits/DropShadowWidget.cpp \
    Sources/Kits/customFrame.cpp \
    Sources/Kits/customLabel.cpp \
    Sources/Kits/customScrollArea.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/guidedialog.cpp \
    Sources/homepagewidget.cpp \
    Sources/settingspagewidget.cpp


HEADERS += \
    Headers/Kits/DropShadowDialog.h \
    Headers/Kits/DropShadowWidget.h \
    Headers/Kits/customFrame.h \
    Headers/Kits/customLabel.h \
    Headers/Kits/customScrollArea.h \
    Headers/Kits/qstylesheetloader.h \
    Headers/Kits/_utility.h \
    Headers/mainwindow.h \
    Headers/guidedialog.h \   
    Headers/homepagewidget.h \
    Headers/settingspagewidget.h

win32{
SOURCES += \
    Sources/Kits/WindWMAPI.cpp

HEADERS += \
    Headers/Kits/WindWMAPI.h
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
