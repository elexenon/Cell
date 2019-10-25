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

#include <QScrollArea>

#include "qstylesheetloader.h"

namespace UTILITY{
    extern void setDropShadowEffect(QList<QGraphicsDropShadowEffect*> animis,QList<QWidget*> modules,QPoint offset,QColor color,
                                    int blurRadius);
    extern void setPropertyAnimation(QList<QPropertyAnimation*> animis,QByteArray _property, QVariant s_value, QVariant e_value,
                                     int duration, QEasingCurve curve, QList<QWidget*> modules,QGraphicsEffect *effect = nullptr);
    extern void multiModulesOneStyleSheet(QList<QWidget*> modules, QString qss);
}

enum FADE_TYPE{_IN, _OUT};

enum PAGE_TYPE{_HOME, _SETTINGS};

enum COLOR_SCHEME{_BRIGHT, _DARK};

enum WINDOW_TYPE{_MAIN, _CHILD};

Q_DECLARE_METATYPE(COLOR_SCHEME);

extern const QString IMG_DIR;
extern const QString FONT_DIR;
extern const QString STYLESHEET_DIR;
extern const QString LIB_DIR;
extern const QString COLOR_SPACE_GRAY;
extern QStyleSheetLoader *styleSheetLoader;
extern const QColor COLOR_OPTION_BLOCK_DARK;
extern const QColor COLOR_OPTION_BLOCK_BRIGHT;
extern const QColor MAINWINDOW_DARK;
extern const QColor MAINWINDOW_BRIGHT;

#endif

