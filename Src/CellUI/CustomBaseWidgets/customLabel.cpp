// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customLabel.h"

customLabel::customLabel(const QString &qss, QWidget *parent):
    QLabel(parent),
    BASEQSS(qss)
{}

void customLabel::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customLabel::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    CellUiGlobal::setPropertyAnimation({animi},
                                      "color",
                                       color(),
                                       m_color,
                                       CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                       QEasingCurve::InOutCubic,
                                      {this}, nullptr);
}
