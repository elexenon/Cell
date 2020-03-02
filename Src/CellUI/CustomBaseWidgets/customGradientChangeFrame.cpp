// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customGradientChangeFrame.h"
#include "../../CellCore/Kits/CellUtility.h"

customGradientChangeFrame::customGradientChangeFrame(const CellVariant &specialColor,QWidget *parent):
    customFrame(customFrame::Regular, parent),
    mSpecialColor(specialColor.toColor())
{}

void customGradientChangeFrame::transCurrState(const customGradientChangeFrame::State &newState)
{
    if(newState == currState) return;
    currState = newState;
    const QColor targetColor = (newState == State::Special ? mSpecialColor :
                                (m_mode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor));
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
    if(currState == State::Special) return;
    const QColor targetColor = (mode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
    CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                      color(),
                                      targetColor,
                                      static_cast<int>(Cell::AnimiDuration::GlobalDuration),
                                      QEasingCurve::InOutCubic,
                                      {this}, nullptr);
}
