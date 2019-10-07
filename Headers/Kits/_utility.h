#pragma once

#ifdef Q_OS_WIN32
#include <windows.h>

#endif

#include <QString>

#include <QScrollBar>

#include <QFontDatabase>

#include <QDebug>

#include <QSize>

#include <QPoint>

#include <QTimer>

#include <QMouseEvent>

#include <QFile>

#include <QDesktopWidget>

#include <QProxyStyle>

#include <QPainter>

#include <QProxyStyle>

#include <QStyleOptionTab>

#include <QList>

#include <QLibrary>

#include <QGraphicsOpacityEffect>

#include <QPropertyAnimation>

#include <typeinfo>

#include <QMetaType>

#include <QPropertyAnimation>

#include "qstylesheetloader.h"

enum FADE_TYPE{_IN, _OUT};

enum PAGE_TYPE{_HOME, _SETTINGS};

enum COLOR_SCHEME{_BRIGHT, _DARK};
Q_DECLARE_METATYPE(COLOR_SCHEME);

static const QString IMG_DIR = ":/images/Share/images/";

static const QString FONT_DIR = ":/fonts/Share/fonts/";

static const QString STYLESHEET_DIR = "C:\\Users\\HengyiYu\\Desktop\\Projects\\c++\\Qt\\Cell_DeepLearning\\Share\\styleSheets\\";

static const QString LIB_DIR = ":/libs/Share/libs/";

static const QString COLOR_SPACE_GRAY = "#798186";

static QStyleSheetLoader *styleSheetLoader = new QStyleSheetLoader(STYLESHEET_DIR);

