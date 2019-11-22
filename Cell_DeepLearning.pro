QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CELL_LAUNCH

TEMPLATE = app

CONFIG += c++11

CONFIG += procompile_header

CONFIG += resources_big

PRECOMPILED_HEADER = Stable.h

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Sources/Kits/cellProject.cpp \
    Sources/Kits/cell_util.cpp \
    Sources/Kits/customDialog.cpp \
    Sources/Kits/customDynamicButton.cpp \
    Sources/Kits/customFrame.cpp \
    Sources/Kits/customLabel.cpp \
    Sources/Kits/customNotificationCenter.cpp \
    Sources/Kits/customStaticButton.cpp \
    Sources/Kits/customWidget.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/guidedialog.cpp \
    Sources/homepagewidget.cpp \
    Sources/newProjectDialog.cpp \
    Sources/settingspagewidget.cpp \
    Sources/workshop.cpp \
    Sources/wswelcomedialog.cpp


HEADERS += \
    Headers/Kits/cellProject.h \
    Headers/Kits/cell_util.h \
    Headers/Kits/customDialog.h \
    Headers/Kits/customDynamicButton.h \
    Headers/Kits/customFrame.h \
    Headers/Kits/customLabel.h \
    Headers/Kits/customNotificationCenter.h \
    Headers/Kits/qstylesheetloader.hpp \
    Headers/kits/customStaticButton.h \
    Headers/kits/customWidget.h \
    Headers/mainwindow.h \
    Headers/guidedialog.h \
    Headers/newProjectDialog.h \
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
    Forms/workshop.ui \
    Forms/wswelcomedialog.ui

INCLUDEPATH += Share/third-part-apis/QScintilla_gpl-2.11.2/Qt4Qt5

LIBS += C:\Users\HengyiYu\Desktop\Projects\c++\Qt\LIBS\X86\qscintilla2_qt5d.dll
#LIBS += Share/libs/X86/qscintilla2_qt5.dll


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Fonts.qrc \
    Images.qrc \
    StyleSheets.qrc

RC_ICONS = CELL.ico
