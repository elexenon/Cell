QT += core gui
QT += widgets  #Only On Qt5

PRECOMPILED_HEADER = Pch.h

CONFIG += c++17
CONFIG += precompile_header
CONFIG += debug_and_release

MYLIBDIR = "C:\Users\fijiisland\Desktop\Projects\Dependency\X64"

CONFIG(debug, debug | release){
    LIBS += -L$$MYLIBDIR -lqscintilla2_qt5d -lsqlite3
}else{
    LIBS += -L$$MYLIBDIR -lqscintilla2_qt5 -lsqlite3
}

INCLUDEPATH += $$PWD/Src/third-part-apis/QScintilla_gpl-2.11.2/ \
               $$PWD/Src/third-part-apis/Sqlite3/

TARGET = CWS64

RC_ICONS = CELL.ico

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    CellDevelopTestStation.cpp \
    Src/CellCore/Kits/CellUtility.cpp \
    Src/CellCore/Kits/WindWMAPI.cpp \
    Src/CellCore/CellSqlManager.cpp \
    Src/CellCore/CellVariant.cpp \
    Src/CellCore/CellProjectEntity.cpp \
    Src/CellUI/CustomBaseWidgets/ButtonWithIconTextHint.cpp \
    Src/CellUI/CustomBaseWidgets/ButtonWithIconText.cpp \
    Src/CellUI/CustomBaseWidgets/ButtonWithIcon.cpp \
    Src/CellUI/CustomBaseWidgets/ButtonWithText.cpp \
    Src/CellUI/CustomBaseWidgets/CellWidgetGlobalInterface.cpp \
    Src/CellUI/CustomBaseWidgets/Processing.cpp \
    Src/CellUI/CustomBaseWidgets/customButton.cpp \
    Src/CellUI/CustomBaseWidgets/customButtonListWidget.cpp \
    Src/CellUI/CustomBaseWidgets/customDialogButton.cpp \
    Src/CellUI/CustomBaseWidgets/customFlowLayout.cpp \
    Src/CellUI/CustomBaseWidgets/customLineEdit.cpp \
    Src/CellUI/CustomBaseWidgets/customListButton.cpp \
    Src/CellUI/CustomBaseWidgets/customMaskDialog.cpp \
    Src/CellUI/CustomBaseWidgets/customNavigator.cpp \
    Src/CellUI/CustomBaseWidgets/customOptionBlock.cpp \
    Src/CellUI/CustomBaseWidgets/customOptionBlockItem.cpp \
    Src/CellUI/CustomBaseWidgets/customScrollArea.cpp \
    Src/CellUI/CustomBaseWidgets/customScrollBlock.cpp \
    Src/CellUI/CustomBaseWidgets/customScrollBlockItem.cpp \
    Src/CellUI/CustomBaseWidgets/customStackedWidget.cpp \
    Src/CellUI/CustomBaseWidgets/customSwitch.cpp \
    Src/CellUI/CustomBaseWidgets/customSwitchFrame.cpp \
    Src/CellUI/CustomBaseWidgets/customTitleBar.cpp \
    Src/CellUI/CustomBaseWidgets/customWinstyleDialog.cpp \
    Src/CellUI/CustomBaseWidgets/customWinstyleWidget.cpp \
    Src/CellUI/CustomBaseWidgets/newPJPageBase.cpp \
    Src/CellUI/CustomBaseWidgets/optionBlockBase.cpp \
    Src/CellUI/Widgets/DeepSense.cpp \
    Src/CellUI/Widgets/HomeStackGrid.cpp \
    Src/CellUI/Widgets/HomeStackList.cpp \
    Src/CellUI/Widgets/LauncherNewPJDialog.cpp \
    Src/CellUI/Widgets/LauncherNewPJGUI.cpp \
    Src/CellUI/Widgets/NewPJGUIModel.cpp \
    Src/CellUI/Widgets/NewPJProjectCellPage.cpp \
    Src/main.cpp \
    Src/CellUI/CustomBaseWidgets/customFrame.cpp \
    Src/CellUI/CustomBaseWidgets/customLabel.cpp \
    Src/CellUI/CustomBaseWidgets/customNotificationCenter.cpp \
    Src/CellUI/Widgets/Launcher.cpp \
    Src/CellUI/Widgets/LauncherGuideDialog.cpp \
    Src/CellUI/Widgets/LauncherHomepage.cpp \
    Src/CellUI/Widgets/LauncherSettings.cpp \
    Src/CellUI/Widgets/WorkShop.cpp \
    Src/CellUI/Widgets/WSLoadingDialog.cpp

HEADERS += \
    CellDevelopTestStation.h \
    Pch.h \
    Src/CellCore/CellNamespace.h \
    Src/CellCore/CellSettings.h \
    Src/CellCore/CellSqlManager.h \
    Src/CellCore/CellVariant.h \
    Src/CellCore/Kits/CellGlobalMacros.h \
    Src/CellCore/Kits/CellUtility.h \
    Src/CellCore/Kits/WindWMAPI.h \
    Src/CellCore/CellProjectEntity.h \
    Src/CellCore/Kits/textFileLoader.hpp \
    Src/CellUI/CustomBaseWidgets/ButtonWithIcon.h \
    Src/CellUI/CustomBaseWidgets/ButtonWithIconText.h \
    Src/CellUI/CustomBaseWidgets/ButtonWithIconTextHint.h \
    Src/CellUI/CustomBaseWidgets/ButtonWithText.h \
    Src/CellUI/CustomBaseWidgets/CellWidgetGlobalInterface.h \
    Src/CellUI/CustomBaseWidgets/Processing.h \
    Src/CellUI/CustomBaseWidgets/customButton.h \
    Src/CellUI/CustomBaseWidgets/customButtonListWidget.h \
    Src/CellUI/CustomBaseWidgets/customDialogButton.h \
    Src/CellUI/CustomBaseWidgets/customFlowLayout.h \
    Src/CellUI/CustomBaseWidgets/customFrame.h \
    Src/CellUI/CustomBaseWidgets/customLabel.h \
    Src/CellUI/CustomBaseWidgets/customLineEdit.h \
    Src/CellUI/CustomBaseWidgets/customListButton.h \
    Src/CellUI/CustomBaseWidgets/customMaskDialog.h \
    Src/CellUI/CustomBaseWidgets/customNavigator.h \
    Src/CellUI/CustomBaseWidgets/customNotificationCenter.h \
    Src/CellUI/CustomBaseWidgets/customOptionBlock.h \
    Src/CellUI/CustomBaseWidgets/customOptionBlockItem.h \
    Src/CellUI/CustomBaseWidgets/customScrollArea.h \
    Src/CellUI/CustomBaseWidgets/customScrollBlock.h \
    Src/CellUI/CustomBaseWidgets/customScrollBlockItem.h \
    Src/CellUI/CustomBaseWidgets/customStackedWidget.h \
    Src/CellUI/CustomBaseWidgets/customSwitch.h \
    Src/CellUI/CustomBaseWidgets/customSwitchFrame.h \
    Src/CellUI/CustomBaseWidgets/customTitleBar.h \
    Src/CellUI/CustomBaseWidgets/customWinstyleDialog.h \
    Src/CellUI/CustomBaseWidgets/customWinstyleWidget.h \
    Src/CellUI/CustomBaseWidgets/newPJPageBase.h \
    Src/CellUI/CustomBaseWidgets/optionBlockBase.h \
    Src/CellUI/Widgets/DeepSense.h \
    Src/CellUI/Widgets/HomeStackGrid.h \
    Src/CellUI/Widgets/HomeStackList.h \
    Src/CellUI/Widgets/Launcher.h \
    Src/CellUI/Widgets/LauncherGuideDialog.h \
    Src/CellUI/Widgets/LauncherHomepage.h \
    Src/CellUI/Widgets/LauncherNewPJDialog.h \
    Src/CellUI/Widgets/LauncherNewPJGUI.h \
    Src/CellUI/Widgets/LauncherSettings.h \
    Src/CellUI/Widgets/NewPJGUIModel.h \
    Src/CellUI/Widgets/NewPJProjectCellPage.h \
    Src/CellUI/Widgets/WorkShop.h \
    Src/CellUI/Widgets/WSLoadingDialog.h

FORMS += \
    CellDevelopTestStation.ui \
    CellResourcesFiles/Forms/WSLoadingDialog.ui

RESOURCES += \
    CellResourcesFiles/Fonts.qrc \
    CellResourcesFiles/Images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
