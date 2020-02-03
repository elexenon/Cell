// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customFrame.h"

#include <QDebug>

customFrame::customFrame(QWidget *parent):
    QFrame(parent)
{}

void customFrame::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customFrame::setBaseQss(const QString& qss)
{
    if(qss == CellUiConst::QSS_CUSTOMFRAME_RADIUS)
        setObjectName(CHAR2STR("customFrameRadius"));
    CellWidgetGlobalInterface::setBaseQss(qss);
}

void customFrame::changeToColor(const QColor& startColor, const QColor &targetColor)
{
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 startColor,
                                 targetColor,
                                 colorChangeAnimiDuration,
                                 easingCurve,
                                 {this},nullptr);
}

void customFrame::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    CellWidgetGlobalInterface::setColorScheme(mode);
}
