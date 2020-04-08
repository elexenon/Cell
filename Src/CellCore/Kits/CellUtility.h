// This Module Declares Universal Values & Functions For Developping.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELL_UTIL_H
#define CELL_UTIL_H

#include "../CellNamespace.h"

namespace CellUiLiteral{
extern const char* const  INSTANCE_IS_ON;
extern const QString IMG_DIR;
extern const QString FONT_DIR;
extern const QString STYLESHEET_DIR;
extern const QString LIB_DIR;
} // namespace CellUiLiteral{

class QGraphicsDropShadowEffect;
class QPropertyAnimation;
class textFileLoader;
class QGraphicsEffect;
class QStackedWidget;
class QGraphicsOpacityEffect;
class QFrame;
class QLabel;

namespace CellUiGlobal{
extern textFileLoader& loader;
//! Set The Same Drop Shadow
//! Effect For Multi Widgets.
extern void setDropShadowEffect(QList<QGraphicsDropShadowEffect*> &&animis,
                                const QList<QWidget*> &modules,
                                const QPoint &offset,
                                const QColor &color, int blurRadius);
//! Set The Same Drop Shadow
//! Effect For One Widget.
extern void setDropShadowEffect(QWidget* module,
                                const QPoint &offset,
                                const QColor &color, int blurRadius);
//! Set The Same PropertyAnimation
//! For Multi Widgets.
extern void setPropertyAnimation(QList<QPropertyAnimation*> &&animis,
                                 const QByteArray &_property,
                                 const QVariant &s_value,
                                 const QVariant &e_value, int duration,
                                 QEasingCurve curve,
                                 const QList<QWidget*> &modules,
                                 QGraphicsEffect *effect = nullptr);
//! Set PropertyAnimation
//! For Single Widget.
extern void setPropertyAnimation(QPropertyAnimation &animi,
                                 QWidget* module,
                                 const QByteArray &property,
                                 const QVariant &sValue,
                                 const QVariant &eValue, int duration,
                                 QEasingCurve curve);
//! Set Fade In & Out Animation
//! For A Specific Target Widget.
extern void setFadeInOrOutAnimation(QGraphicsOpacityEffect *eff,
                                    QPropertyAnimation *animi,
                                    QWidget *target,
                                    int duration,
                                    Cell::FadeAnimiType type);
//! Get A Line
//! Which Is One Pixel Height OR WIDTH.
extern QFrame* getLine(Cell::LineType type);
//! Get Font By Ordered Font Name.
//! If The Font Cannot Be Found In
//! Font Families Of Current Platform,
//! This Founction Will Return A Font Which's
//! Specified By User.
extern QFont   getFont(const QString &fontName, int pixelSize);
//! Return A QString Form Of Current Time.
extern QString getProjectTime();

extern bool hasAttribute(int flag, int mask);

extern bool hasNoAttribute(int flag, int mask);

//! Set Custom Label.
extern void    setCustomTextLabel(QLabel *label, const QString& fontName, int fontPixelSize, const QString& text = " ");
//! Set The Same StyleSheet
//! For Multi Widgets.
extern void    multiModulesOneStyleSheet(const QList<QWidget*> &modules, const QString &qss);
//! Set Pixmap
//! For A Specific Target QLabel.
extern void    setLabelPixmap(QLabel *label, const QString& fileName, int iconWidth, int iconHeight);
//! Set Page Switch Animation
//! For Target Pages.
extern void    setPageSwitchAnimation(QStackedWidget *stackedWidget, QWidget *targetPage, QPropertyAnimation *animiPtr);
} // namespace CellUiGlobal{

#endif
