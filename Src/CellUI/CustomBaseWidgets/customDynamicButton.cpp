// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customDynamicButton.h"
#include "../../CellCore/Kits/CellUtility.h"

customDynamicButton::customDynamicButton(QWidget *parent):
    customStaticButton(parent),
    BASEQSS(CellUiConst::QSS_CUSTOMBUTTON_DYNAMIC)
{}

void customDynamicButton::setBrightModeEnterLeaveColor(const QColor &e, const QColor &l){
    brightModeEnterColor = e; brightModeLeaveColor = l;
    m_color = brightModeLeaveColor;
    brightModeCheckedColor = brightModeEnterColor;
}

void customDynamicButton::setDarkModeEnterLeaveColor(const QColor &e, const QColor &l){
    darkModeEnterColor = e;   darkModeLeaveColor = l;
    darkModeCheckedColor = darkModeEnterColor;
    setStyleSheet(BASEQSS.arg(m_color.red()).arg(m_color.green()).arg(m_color.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue()));
}

void customDynamicButton::enterEvent(QEvent*){
    if(!this->isChecked()){
        QColor enterColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightModeEnterColor : darkModeEnterColor);
        CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     enterColor,
                                     animiDuration,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    }
}

void customDynamicButton::leaveEvent(QEvent*){
    if(!this->isChecked()){
        QColor leaveColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightModeLeaveColor : darkModeLeaveColor);
        CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     leaveColor,
                                     animiDuration,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    }
}

void customDynamicButton::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}
