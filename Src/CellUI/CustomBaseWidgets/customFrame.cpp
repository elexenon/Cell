// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customFrame.h"

#include <QDebug>

customFrame::customFrame(const QString &qss, QWidget *parent):
    QFrame(parent),
    BASEQSS(qss)
{
    if(qss == CellUiConst::QSS_CUSTOMFRAME_RADIUS)
        setObjectName(CHAR2STR("customFrameRadius"));
}

void customFrame::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customFrame::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
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
