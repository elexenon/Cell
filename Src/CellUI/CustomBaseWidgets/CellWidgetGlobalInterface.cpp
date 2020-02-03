// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../CustomBaseWidgets/CellWidgetGlobalInterface.h"

void CellWidgetGlobalInterface::setBrightDarkModeColor(const QColor &b, const QColor &d)
{
    brightmodeColor = b; darkmodeColor = d;
    setColor(brightmodeColor);
}

void CellWidgetGlobalInterface::setColor(const QColor &color)
{
    m_color = color;
}

void CellWidgetGlobalInterface::setBaseQss(const QString& qss){
    this->BASEQSS = qss;
}

void CellWidgetGlobalInterface::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    const QColor targetColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightmodeColor : darkmodeColor);
    changeToColor(color(),targetColor);
}
