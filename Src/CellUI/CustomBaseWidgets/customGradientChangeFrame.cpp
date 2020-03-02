// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customGradientChangeFrame.h"

customGradientChangeFrame::customGradientChangeFrame(const CellVariant &specialColor,QWidget *parent):
    customFrame(customFrame::_REGULAR, parent),
    mSpecialColor(specialColor.toColor())
{}

void customGradientChangeFrame::transCurrState(const customGradientChangeFrame::GRADIENT_STATE &newState)
{
    if(newState == currState) return;
    currState = newState;
    const QColor targetColor = (newState == GRADIENT_STATE::_SPECIAL ? mSpecialColor :
                                (m_mode == Cell::ColorScheme::_BRIGHT ? brightmodeColor : darkmodeColor));
    CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     targetColor,
                                     800,
                                     QEasingCurve::InOutCubic,
    {this},nullptr);
}

void customGradientChangeFrame::setColorScheme(Cell::ColorScheme mode){
    if(mode == m_mode) return;
    m_mode = mode;
    if(currState == GRADIENT_STATE::_SPECIAL) return;
    const QColor targetColor = (mode == Cell::ColorScheme::_BRIGHT ? brightmodeColor : darkmodeColor);
    CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                      color(),
                                      targetColor,
                                      static_cast<int>(Cell::GlobalDuration),
                                      QEasingCurve::InOutCubic,
                                      {this}, nullptr);
}
