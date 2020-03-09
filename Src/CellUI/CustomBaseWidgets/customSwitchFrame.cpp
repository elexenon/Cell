// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customSwitchFrame.h"
#include "../../CellCore/Kits/CellUtility.h"

customSwitchFrame::customSwitchFrame(const CellVariant &specialColor,QWidget *parent):
    customFrame(customFrame::Type::Regular, parent),
    mSpecialColor(specialColor.toColor())
{}

void customSwitchFrame::transCurrState(const customSwitchFrame::State &newState)
{
    if(newState == currState) return;
    currState = newState;
    const QColor targetColor = (newState == State::Special ? mSpecialColor :
                                (CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor));
    customFrame::changeToColor(mColor, targetColor, static_cast<int>(Cell::AnimiDuration::GlobalDuration));
}

void customSwitchFrame::setColorScheme(Cell::ColorScheme mode){
    if(mode == CellWidgetGlobalInterface::mMode) return;
    CellWidgetGlobalInterface::mMode = mode;
    if(currState == State::Special) return;
    const QColor targetColor = (mode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
    customFrame::changeToColor(mColor, targetColor, static_cast<int>(Cell::AnimiDuration::GlobalDuration));
}
