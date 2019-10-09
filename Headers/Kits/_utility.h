/*
 *
 *      CREATED BY HENGYI YU 2019/10/1
 *
 */
#ifndef _UTILITY_H
#define _UTILITY_H

#include <windows.h>

#include <QString>

#include <QScrollBar>

#include <QFontDatabase>

#include <QDebug>

#include <QTime>

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

#include <QParallelAnimationGroup>

#include <QScrollArea>

#include "qstylesheetloader.h"

namespace UTILITY{

static void setPropertyAnimation(QPropertyAnimation* animi,QByteArray _property, QVariant s_value, QVariant e_value,
                                 int duration, QEasingCurve curve, QWidget *target, bool startNow,
                                 QGraphicsEffect *effect = nullptr)
{
    if(!effect)
        animi = new QPropertyAnimation(target, _property);
    else
        animi = new QPropertyAnimation(effect, _property);
    animi->setDuration(duration);
    animi->setEasingCurve(curve);
    animi->setStartValue(s_value);
    animi->setEndValue(e_value);
    if(startNow) animi->start(QAbstractAnimation::DeleteWhenStopped);   // Bug here.
}

}

enum FADE_TYPE{_IN, _OUT};

enum PAGE_TYPE{_HOME, _SETTINGS};

enum COLOR_SCHEME{_BRIGHT, _DARK};

enum WINDOW_TYPE{_MAIN, _CHILD};

Q_DECLARE_METATYPE(COLOR_SCHEME);

static const QString IMG_DIR = ":/images/Share/images/";

static const QString FONT_DIR = ":/fonts/Share/fonts/";

static const QString STYLESHEET_DIR = "C:\\Users\\HengyiYu\\Desktop\\Projects\\c++\\Qt\\Cell_DeepLearning\\Share\\styleSheets\\";

static const QString LIB_DIR = ":/libs/Share/libs/";

static const QString COLOR_SPACE_GRAY = "#798186";

static QStyleSheetLoader *styleSheetLoader = new QStyleSheetLoader(STYLESHEET_DIR);

static const QColor COLOR_OPTION_BLOCK_DARK(44, 44, 45);

static const QColor COLOR_OPTION_BLOCK_BRIGHT(218, 218, 218);

static const QColor MAINWINDOW_DARK(31, 30, 31);

static const QColor MAINWINDOW_BRIGHT(247, 247, 247);

#endif

