// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "../CustomBaseWidgets/CellWidgetGlobalInterface.h"

void CellWidgetGlobalInterface::setBrightDarkModeColor(const CellVariant &b, const CellVariant &d)
{
    brightmodeColor = b.toColor(); darkmodeColor = d.toColor();
    setColor(brightmodeColor);
}

void CellWidgetGlobalInterface::setEventConnections()
{

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
    changeToColor(color(), targetColor, colorSchemeAnimiDuration);
}
