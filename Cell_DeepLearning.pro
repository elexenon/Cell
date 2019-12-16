QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cell_Launcher

TEMPLATE = app

CONFIG += c++11

CONFIG += procompile_header

PRECOMPILED_HEADER = Src/CellCore/Kits/Pch.h

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Src/CellUI/CustomBaseWidgets/customGradientChangeFrame.cpp \
    Src/CellUI/CustomBaseWidgets/customLine.cpp \
    Src/CellUI/Widgets/NewPJProjectPage.cpp \
    Src/main.cpp \
    Src/CellCore/Kits/CellUtility.cpp \
    Src/CellCore/Kits/WindWMAPI.cpp \
    Src/CellCore/CellProjectEntity.cpp \
    Src/CellUI/CustomBaseWidgets/customDialog.cpp \
    Src/CellUI/CustomBaseWidgets/customDynamicButton.cpp \
    Src/CellUI/CustomBaseWidgets/customFrame.cpp \
    Src/CellUI/CustomBaseWidgets/customLabel.cpp \
    Src/CellUI/CustomBaseWidgets/customNotificationCenter.cpp \
    Src/CellUI/CustomBaseWidgets/customStaticButton.cpp \
    Src/CellUI/CustomBaseWidgets/customWidget.cpp \
    Src/CellUI/Widgets/Launcher.cpp \
    Src/CellUI/Widgets/LauncherGuideDialog.cpp \
    Src/CellUI/Widgets/LauncherHomepage.cpp \
    Src/CellUI/Widgets/LauncherSettings.cpp \
    Src/CellUI/Widgets/WorkShop.cpp \
    Src/CellUI/Widgets/WSLoadingDialog.cpp \
    Src/CellUI/Widgets/launcherNewPJDialog.cpp


HEADERS += \
    Src/CellCore/Kits/CellUtility.h \
    Src/CellCore/Kits/CustomCppInterfaceDefination.h \
    Src/CellCore/Kits/WindWMAPI.h \
    Src/CellCore/Kits/StyleSheetLoader.hpp \
    Src/CellCore/CellProjectEntity.h \
    Src/CellUI/CustomBaseWidgets/customDialog.h \
    Src/CellUI/CustomBaseWidgets/customDynamicButton.h \
    Src/CellUI/CustomBaseWidgets/customFrame.h \
    Src/CellUI/CustomBaseWidgets/customGradientChangeFrame.h \
    Src/CellUI/CustomBaseWidgets/customLabel.h \
    Src/CellUI/CustomBaseWidgets/customLine.h \
    Src/CellUI/CustomBaseWidgets/customNotificationCenter.h \
    Src/CellUI/CustomBaseWidgets/customStaticButton.h \
    Src/CellUI/CustomBaseWidgets/customWidget.h \
    Src/CellUI/Widgets/Launcher.h \
    Src/CellUI/Widgets/LauncherGuideDialog.h \
    Src/CellUI/Widgets/LauncherHomepage.h \
    Src/CellUI/Widgets/LauncherSettings.h \
    Src/CellUI/Widgets/NewPJProjectPage.h \
    Src/CellUI/Widgets/WorkShop.h \
    Src/CellUI/Widgets/WSLoadingDialog.h \
    Src/CellUI/Widgets/launcherNewPJDialog.h

FORMS += \
    Src/CellUI/Widgets/Forms/Launcher.ui \
    Src/CellUI/Widgets/Forms/LauncherGuideDialog.ui \
    Src/CellUI/Widgets/Forms/LauncherHomepage.ui \
    Src/CellUI/Widgets/Forms/WorkShop.ui \
    Src/CellUI/Widgets/Forms/WSLoadingDialog.ui \
    Src/CellUI/Widgets/Forms/launcherNewPJDialog.ui

RESOURCES += \
    Src/CellResourcesFiles/Fonts.qrc \
    Src/CellResourcesFiles/Images.qrc \
    Src/CellResourcesFiles/StyleSheets.qrc

INCLUDEPATH += Src/third-part-apis/QScintilla_gpl-2.11.2/Qt4Qt5

CONFIG += debug_and_release

# Libs Path has to be an absolute directory.
CONFIG(debug, debug | release){
    LIBS += C:\Users\HengyiYu\Desktop\Projects\c++\Qt\LIBS\X86\qscintilla2_qt5d.dll
}else{
    LIBS += C:\Users\HengyiYu\Desktop\Projects\c++\Qt\LIBS\X86\qscintilla2_qt5.dll
}

RC_ICONS = CELL.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
