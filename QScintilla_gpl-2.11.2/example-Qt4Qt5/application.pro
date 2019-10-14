QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = app

CONFIG      += qscintilla2

INCLUDEPATH += C:\Users\HengyiYu\Desktop\Projects\c++\Qt\Cell_DeepLearning\QScintilla_gpl-2.11.2\Qt4Qt5

macx {
    QMAKE_POST_LINK = install_name_tool -change libqscintilla2_qt$${QT_MAJOR_VERSION}.15.dylib $$[QT_INSTALL_LIBS]/libqscintilla2_qt$${QT_MAJOR_VERSION}.15.dylib $(TARGET)
}

HEADERS      = mainwindow.h
SOURCES      = main.cpp mainwindow.cpp
RESOURCES    = application.qrc
