// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customStaticButton.h"
#include "../../CellCore/Kits/CellUtility.h"

customStaticButton::customStaticButton(QWidget *parent):
    QPushButton(parent),
    BASEQSS(CellUiConst::QSS_CUSTOMBUTTON_STATIC)
{}

void customStaticButton::setBrightModeCheckedUncheckedColor(const QColor &c, const QColor &u){
    brightModeCheckedColor = c; brightModeLeaveColor = u;
    m_color = brightModeLeaveColor;
}

void customStaticButton::setDarkModeCheckedUncheckedColor(const QColor &c, const QColor &u){
    darkModeCheckedColor = c; darkModeLeaveColor = u;
    setStyleSheet(BASEQSS.arg(m_color.red()).arg(m_color.green()).arg(m_color.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue()));
}

void customStaticButton::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    QColor startColor;
    QColor endColor;
    if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        m_mode = CellUiGlobal::COLOR_SCHEME::_DARK;
        if(!isChecked()){
            startColor = m_color;
            endColor = darkModeLeaveColor;
        }else{
            startColor = brightModeCheckedColor;
            endColor = darkModeCheckedColor;
            m_color = darkModeLeaveColor;
        }
        CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                     startColor,
                                     endColor,
                                     CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    }else if(mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT){
        m_mode = CellUiGlobal::COLOR_SCHEME::_BRIGHT;
        if(!isChecked()){
            startColor = m_color;
            endColor = brightModeLeaveColor;
        }else{
            startColor = darkModeCheckedColor;
            endColor = brightModeCheckedColor;
            m_color = brightModeLeaveColor;
        }
        CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                     startColor,
                                     endColor,
                                     CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
        {this},nullptr);
    }
}

void customStaticButton::setColor(const QColor &color)
{
    if(!isChecked()){
        CellWidgetGlobalInterface::setColor(color);
        QColor checkedColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightModeCheckedColor : darkModeCheckedColor);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue())
                      .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue()));
    }else
        setStyleSheet(BASEQSS.arg(m_color.red()).arg(m_color.green()).arg(m_color.blue())
                      .arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(color.red()).arg(color.green()).arg(color.blue()));
}
