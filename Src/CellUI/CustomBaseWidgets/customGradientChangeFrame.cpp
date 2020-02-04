// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customGradientChangeFrame.h"

customGradientChangeFrame::customGradientChangeFrame(const QColor &specialColor,QWidget *parent):
    customFrame(customFrame::_REGULAR, parent),
    specialColor(specialColor)
{

}

void customGradientChangeFrame::transCurrState(const customGradientChangeFrame::GRADIENT_STATE &newState)
{
    if(newState == currState) return;
    currState = newState;
    const QColor targetColor = (newState == GRADIENT_STATE::_SPECIAL ? specialColor :
                                (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? CellUiConst::GRAYLEVEL218 : CellUiConst::GRAYLEVEL70));
    CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     targetColor,
                                     800,
                                     QEasingCurve::InOutCubic,
    {this},nullptr);
}

void customGradientChangeFrame::setColorScheme(CellUiGlobal::COLOR_SCHEME mode){
    if(mode == m_mode) return;
    m_mode = mode;
    if(currState == GRADIENT_STATE::_SPECIAL) return;
    const QColor targetColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightmodeColor : darkmodeColor);
    CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                      color(),
                                      targetColor,
                                      CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                      QEasingCurve::InOutCubic,
                                      {this}, nullptr);
}
