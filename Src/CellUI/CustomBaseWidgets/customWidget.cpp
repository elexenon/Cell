// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customWidget.h"
#include "../../CellCore/Kits/WindWMAPI.h"

customWidget::customWidget(QWidget *parent):
    CellWinstyleWidget(parent)
{}

void customWidget::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customWidget::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    const QColor targetColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightmodeColor : darkmodeColor);
    CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     targetColor,
                                     CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {this}, nullptr);
}
