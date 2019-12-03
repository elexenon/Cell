// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customGradientChangeFrame.h"

customGradientChangeFrame::customGradientChangeFrame(const QString &qss,const QColor &specialColor,QWidget *parent):
    customFrame(qss,parent),
    currState(GRADIENT_STATE::_NORMAL),
    m_mode(CellGlobal::COLOR_SCHEME::_BRIGHT),
    specialColor(specialColor)
{}

void customGradientChangeFrame::transCurrState(const customGradientChangeFrame::GRADIENT_STATE &newState)
{
    if(newState == currState) return;
    currState = newState;
    const QColor targetColor = (newState == GRADIENT_STATE::_SPECIAL ? specialColor :
                                (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? Cell_Const::GRAYLEVEL218 : Cell_Const::GRAYLEVEL70));
    CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     targetColor,
                                     800,
                                     QEasingCurve::InOutCubic,
    {this},nullptr);
}

void customGradientChangeFrame::setColorScheme(CellGlobal::COLOR_SCHEME mode){
    if(mode == m_mode) return;
    m_mode = mode;
    if(currState == GRADIENT_STATE::_SPECIAL) return;
    const QColor targetColor = (mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? Cell_Const::GRAYLEVEL218 : Cell_Const::GRAYLEVEL70);
    CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                      color(),
                                      targetColor,
                                      CellGlobal::CELL_GLOBALANIMIDURATION,
                                      QEasingCurve::InOutCubic,
                                      {this}, nullptr);
}
