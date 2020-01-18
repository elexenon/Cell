// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customButton.h"

customButton::customButton(customButton::TYPE type, QWidget *parent):
    QPushButton(parent),
    type(type)
{
    switch(type){
    case STATIC:
        BASEQSS = CellUiConst::QSS_CUSTOMBUTTON_STATIC;
        setFlat(true);
        break;
    case DYNAMIC:
        BASEQSS = CellUiConst::QSS_CUSTOMBUTTON_DYNAMIC;
        break;
    case CHECKABLE:
        setCheckable(true);
        BASEQSS = CellUiConst::QSS_CUSTOMBUTTON_CHECKABLE;
        break;
    }
}

void customButton::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = CellUiGlobal::COLOR_SCHEME::_DARK;
    QColor startColor;
    QColor endColor;
    setAnimiStartEndColor(mode, startColor, endColor);
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 startColor,
                                 endColor,
                                 CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                 QEasingCurve::InOutCubic,
    {this},nullptr);
}

void customButton::enterEvent(QEvent *)
{
    if(type != DYNAMIC) return;
    QColor enterColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightModeHoveringColor : darkModeHoveringColor);
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 color(),
                                 enterColor,
                                 animiDuration,
                                 QEasingCurve::InOutCubic,
                                 {this},nullptr);
}

void customButton::leaveEvent(QEvent*){
    if(type != DYNAMIC) return;
    QColor leaveColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightmodeColor : darkmodeColor);
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 color(),
                                 leaveColor,
                                 animiDuration,
                                 QEasingCurve::InOutCubic,
                                 {this},nullptr);
}

void customButton::setAnimiStartEndColor(CellUiGlobal::COLOR_SCHEME mode, QColor &startColor,
                                         QColor &endColor)
{
    if(type == CHECKABLE)
    {
        if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
            if(!isChecked()){
                startColor = m_color;
                endColor = darkmodeColor;
            }else{
                startColor = brightModeCheckedColor;
                endColor = darkModeCheckedColor;
                m_color = darkmodeColor;
            }
        }else if(mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT){
            if(!isChecked()){
                startColor = m_color;
                endColor = brightmodeColor;
            }else{
                startColor = darkModeCheckedColor;
                endColor = brightModeCheckedColor;
                m_color = brightmodeColor;
            }
        }
    }
    else if(type == DYNAMIC || type == STATIC)
    {
        startColor = color();
        endColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightmodeColor : darkmodeColor);
    }
}

void customButton::setColor(const QColor &color)
{
    if(type == CHECKABLE)
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
    else if(type == DYNAMIC)
    {
        CellWidgetGlobalInterface::setColor(color);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
    }
    else if(type == STATIC)
    {
        CellWidgetGlobalInterface::setColor(color);
        QColor hoverColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightModeHoverColor : darkModeHoverColor);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(hoverColor.red()).arg(hoverColor.green()).arg(hoverColor.blue()));
    }
}

