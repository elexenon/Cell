// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customLabel.h"
#include "../../CellCore/Kits/CellUtility.h"

customLabel::customLabel(QWidget *parent):
    QLabel(parent)
{
    init();
    setEventConnections();
}

void customLabel::init(){
    setAutoFillBackground(true);
}

void customLabel::setEventConnections(){
    CellWidgetGlobalInterface::setEventConnections();
}

void customLabel::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(QString("QLabel{color:rgb(%1,%2,%3);background:transparent;}")
                  .arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customLabel::setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor, QColor &endColor){
    CellWidgetGlobalInterface::setAnimiStartEndColor(mode, startColor, endColor);
}

void customLabel::changeToColor(const QColor &startColor, const QColor &targetColor, int duration)
{
    CellUiGlobal::setPropertyAnimation(animi, this, "color",
                                       startColor, targetColor, duration,
                                       CellWidgetGlobalInterface::easingCurve);
}

void customLabel::setColorScheme(Cell::ColorScheme mode)
{
    CellWidgetGlobalInterface::setColorScheme(mode);
}
