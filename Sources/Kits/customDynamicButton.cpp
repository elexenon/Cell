// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/Kits/customDynamicButton.h"
#include "Headers/Kits/cell_util.h"

using namespace CELL_UTIL;

customDynamicButton::customDynamicButton(QWidget *parent):
    customStaticButton(parent),
    BASEQSS(LITERAL::QSS_CUSTOMBUTTON_DYNAMIC)
{}

void customDynamicButton::setBrightModeEnterLeaveColor(const QColor &e, const QColor &l){
    brightModeEnterColor = e; brightModeLeaveColor = l;
}

void customDynamicButton::setDarkModeEnterLeaveColor(const QColor &e, const QColor &l){
    darkModeEnterColor = e;   darkModeLeaveColor = l;
}

void customDynamicButton::Init(){
    m_colorScheme = COLOR_SCHEME::_BRIGHT;
    currColor = brightModeLeaveColor;
    if(isCheckable())
        connect(this, SIGNAL(clicked(bool)), this, SLOT(backToCurrColor()));
    brightModeCheckedColor = brightModeEnterColor;
    darkModeCheckedColor = darkModeEnterColor;
    setStyleSheet(BASEQSS.arg(currColor.red()).arg(currColor.green()).arg(currColor.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue()));
}

void customDynamicButton::enterEvent(QEvent*){
    if(!this->isChecked()){
        QColor enterColor = (m_colorScheme == COLOR_SCHEME::_BRIGHT ? brightModeEnterColor : darkModeEnterColor);
        TOOLS::setPropertyAnimation({animi},
                                     "color",
                                     currColor,
                                     enterColor,
                                     animiDuration,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    }
}

void customDynamicButton::leaveEvent(QEvent*){
    if(!this->isChecked()){
        QColor leaveColor = (m_colorScheme == COLOR_SCHEME::_BRIGHT ? brightModeLeaveColor : darkModeLeaveColor);
        TOOLS::setPropertyAnimation({animi},
                                     "color",
                                     currColor,
                                     leaveColor,
                                     animiDuration,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    }
}

void customDynamicButton::backToCurrColor()
{
    currColor = (m_colorScheme == COLOR_SCHEME::_BRIGHT ? brightModeLeaveColor : darkModeLeaveColor);
    QColor checkedColor = (m_colorScheme == COLOR_SCHEME::_BRIGHT ? brightModeCheckedColor : darkModeCheckedColor);
    setStyleSheet(BASEQSS.arg(currColor.red()).arg(currColor.green()).arg(currColor.blue())
                         .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue()));
}

void customDynamicButton::setAnimationDuration(int dur)
{
    animiDuration = dur;
}

const QColor customDynamicButton::color() const
{
    return currColor;
}

void customDynamicButton::setColor(const QColor &color)
{
    if(!isChecked()){
        currColor = color;
        QColor checkedColor = (m_colorScheme == COLOR_SCHEME::_BRIGHT ? brightModeCheckedColor : darkModeCheckedColor);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                       .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue()));
    }else{
        setStyleSheet(BASEQSS.arg(currColor.red()).arg(currColor.green()).arg(currColor.blue())
                       .arg(color.red()).arg(color.green()).arg(color.blue()));
    }
}
