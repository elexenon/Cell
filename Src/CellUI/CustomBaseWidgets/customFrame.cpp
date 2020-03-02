// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customFrame.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QDebug>

customFrame::customFrame(CustomFrameType type, QWidget *parent):
    QFrame(parent),
    mType(type)
{
    setBaseQss("");
}

void customFrame::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customFrame::setBaseQss(const QString& qss)
{
    (void)qss;
    setObjectName(CHAR2STR("customFrameRadius"));
    QString qssFileName = (mType == CustomFrameType::Regular ? "CustomFrame.css" : "CustomFrameRadius.css");

    CellUiGlobal::loader.setFileName(qssFileName);
    CellWidgetGlobalInterface::setBaseQss(CellUiGlobal::loader.content());
}

void customFrame::changeToColor(const QColor& startColor, const QColor &targetColor, int duration)
{
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 startColor,
                                 targetColor,
                                 duration,
                                 easingCurve,
    {this},nullptr);
}

void customFrame::setEventConnections()
{

}

void customFrame::setColorScheme(Cell::ColorScheme mode)
{
    CellWidgetGlobalInterface::setColorScheme(mode);
}
