QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cell_Launcher

TEMPLATE = app

CONFIG += c++11

CONFIG += procompile_header

PRECOMPILED_HEADER = Src/CellCore/Kits/Pch.h

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    CellDevelopTestStation.cpp \
    Src/CellUI/CustomBaseWidgets/CellWidgetGlobalInterface.cpp \
    Src/CellUI/CustomBaseWidgets/customButton.cpp \
    Src/CellUI/CustomBaseWidgets/customButtonListWidget.cpp \
    Src/CellUI/CustomBaseWidgets/customGradientChangeFrame.cpp \
    Src/CellUI/CustomBaseWidgets/customLine.cpp \
    Src/CellUI/CustomBaseWidgets/customListButton.cpp \
    Src/CellUI/CustomBaseWidgets/customOptionBlock.cpp \
    Src/CellUI/CustomBaseWidgets/customOptionBlockItem.cpp \
    Src/CellUI/CustomBaseWidgets/customOptionBlockSector.cpp \
    Src/CellUI/CustomBaseWidgets/customTitleBar.cpp \
    Src/CellUI/CustomBaseWidgets/customWinstyleDialog.cpp \
    Src/CellUI/CustomBaseWidgets/customWinstyleWidget.cpp \
    Src/CellUI/Widgets/LauncherNewPJDialog.cpp \
    Src/CellUI/Widgets/NewPJProjectCellPage.cpp \
    Src/main.cpp \
    Src/CellCore/Kits/CellUtility.cpp \
    Src/CellCore/Kits/WindWMAPI.cpp \
    Src/CellCore/CellProjectEntity.cpp \
    Src/CellUI/CustomBaseWidgets/customDynamicButton.cpp \
    Src/CellUI/CustomBaseWidgets/customFrame.cpp \
    Src/CellUI/CustomBaseWidgets/customLabel.cpp \
    Src/CellUI/CustomBaseWidgets/customNotificationCenter.cpp \
    Src/CellUI/CustomBaseWidgets/customStaticButton.cpp \
    Src/CellUI/Widgets/Launcher.cpp \
    Src/CellUI/Widgets/LauncherGuideDialog.cpp \
    Src/CellUI/Widgets/LauncherHomepage.cpp \
    Src/CellUI/Widgets/LauncherSettings.cpp \
    Src/CellUI/Widgets/WorkShop.cpp \
    Src/CellUI/Widgets/WSLoadingDialog.cpp


HEADERS += \
    CellDevelopTestStation.h \
    Src/CellCore/Kits/CellGlobalMacros.h \
    Src/CellCore/Kits/CellUtility.h \
    Src/CellCore/Kits/WindWMAPI.h \
    Src/CellCore/Kits/StyleSheetLoader.hpp \
    Src/CellCore/CellProjectEntity.h \
    Src/CellUI/CustomBaseWidgets/CellWidgetGlobalInterface.h \
    Src/CellUI/CustomBaseWidgets/customButton.h \
    Src/CellUI/CustomBaseWidgets/customButtonListWidget.h \
    Src/CellUI/CustomBaseWidgets/customDynamicButton.h \
    Src/CellUI/CustomBaseWidgets/customFrame.h \
    Src/CellUI/CustomBaseWidgets/customGradientChangeFrame.h \
    Src/CellUI/CustomBaseWidgets/customLabel.h \
    Src/CellUI/CustomBaseWidgets/customLine.h \
    Src/CellUI/CustomBaseWidgets/customListButton.h \
    Src/CellUI/CustomBaseWidgets/customNotificationCenter.h \
    Src/CellUI/CustomBaseWidgets/customOptionBlock.h \
    Src/CellUI/CustomBaseWidgets/customOptionBlockItem.h \
    Src/CellUI/CustomBaseWidgets/customOptionBlockSector.h \
    Src/CellUI/CustomBaseWidgets/customStaticButton.h \
    Src/CellUI/CustomBaseWidgets/customTitleBar.h \
    Src/CellUI/CustomBaseWidgets/customWinstyleDialog.h \
    Src/CellUI/CustomBaseWidgets/customWinstyleWidget.h \
    Src/CellUI/Widgets/Launcher.h \
    Src/CellUI/Widgets/LauncherGuideDialog.h \
    Src/CellUI/Widgets/LauncherHomepage.h \
    Src/CellUI/Widgets/LauncherNewPJDialog.h \
    Src/CellUI/Widgets/LauncherSettings.h \
    Src/CellUI/Widgets/NewPJProjectCellPage.h \
    Src/CellUI/Widgets/WorkShop.h \
    Src/CellUI/Widgets/WSLoadingDialog.h

FORMS += \
    CellDevelopTestStation.ui \
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
