// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "../CustomBaseWidgets/CellWidgetGlobalInterface.h"

void CellWidgetGlobalInterface::setBrightDarkColor(const CellVariant &b, const CellVariant &d){
    brightmodeColor = b.toColor();
    darkmodeColor   = d.toColor();
    // ***Polymorphic
    // ***Behavior.
    setColor(brightmodeColor);
}

void CellWidgetGlobalInterface::init()
{}

void CellWidgetGlobalInterface::setEventConnections()
{}
// ***This is a default
// ***implementation.
void CellWidgetGlobalInterface::setColor(const QColor &color){
    mColor = color;
}
// ***This is a default
// ***implementation.
void CellWidgetGlobalInterface::setColorScheme(Cell::ColorScheme mode){
    if(mode == mMode) return;
    mMode = mode;
    QColor sColor, eColor;
    // ***Polymorphic
    // ***Behavior.
    setAnimiStartEndColor(mode, sColor, eColor);
    changeToColor(sColor, eColor, switchDuration);
    if(!_modules.isEmpty())
        for(auto & e : _modules) e->setColorScheme(mode);
}
// ***This is a default
// ***implementation.
void CellWidgetGlobalInterface::setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor, QColor &endColor)
{
    startColor = mColor;
    endColor = mode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor;
}
