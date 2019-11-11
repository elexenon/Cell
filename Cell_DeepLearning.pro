QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CELL_LAUNCH

TEMPLATE = app

CONFIG += c++11

CONFIG += procompile_header

PRECOMPILED_HEADER = Stable.h

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Sources/Kits/cell_util.cpp \
    Sources/Kits/customDialog.cpp \
    Sources/Kits/customFrame.cpp \
    Sources/Kits/customLabel.cpp \
    Sources/Kits/customWidget.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/guidedialog.cpp \
    Sources/homepagewidget.cpp \
    Sources/settingspagewidget.cpp \
    Sources/workshop.cpp \
    Sources/wswelcomedialog.cpp


HEADERS += \
    Headers/Kits/cell_util.h \
    Headers/Kits/customDialog.h \
    Headers/Kits/customFrame.h \
    Headers/Kits/customLabel.h \
    Headers/Kits/qstylesheetloader.hpp \
    Headers/kits/customWidget.h \
    Headers/mainwindow.h \
    Headers/guidedialog.h \
    Headers/workshop.h \
    Headers/homepagewidget.h \
    Headers/settingspagewidget.h \
    Headers/wswelcomedialog.h \
    Stable.h

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
    Forms/settingspagewidget.ui \
    Forms/workshop.ui \
    Forms/wswelcomedialog.ui

INCLUDEPATH += Share/third-part-apis/QScintilla_gpl-2.11.2/Qt4Qt5

LIBS += C:\Users\HengyiYu\Desktop\Projects\c++\Qt\Cell_DeepLearning\Share\libs\X86\qscintilla2_qt5d.dll
#LIBS += Share/libs/X86/qscintilla2_qt5.dll


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc

RC_ICONS = CELL.ico
