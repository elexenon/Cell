// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customButton.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"

customButton::customButton(customButton::TYPE type, QWidget *parent):
    QPushButton(parent),
    type(type)
{
    setBaseQss("");
}

void customButton::setBaseQss(const QString &qss)
{
    (void)qss;
    QString qssFileName;
    switch(type){
    case STATIC:
        qssFileName = "CustomButtonStatic.css";
        setFlat(true);
        break;
    case DYNAMIC:
        qssFileName = "CustomButtonDynamic.css";
        break;
    case CHECKABLE:
        setCheckable(true);
        qssFileName = "CustomButtonCheckable.css";
        break;
    case STATIC_RADIUS:
        qssFileName = "CustomButtonStaticRadius.css";
        setFlat(true);
        break;
    case DYNAMIC_RADIUS:
        qssFileName = "CustomButtonDynamicRadius.css";
        break;
    case CHECKABLE_RADIUS:
        qssFileName = "CustomButtonCheckableRadius.css";
        setCheckable(true);
        break;
    }
    using CellEntityTools::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(qssFileName);
    BASEQSS = styleSheetLoader->styleSheet();
}

void customButton::changeToColor(const QColor &startColor, const QColor &targetColor, int duration)
{
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 startColor,
                                 targetColor,
                                 duration,
                                 easingCurve,
                                 {this},nullptr);
}

void customButton::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = CellUiGlobal::COLOR_SCHEME::_DARK;
    QColor startColor;
    QColor endColor;
    setAnimiStartEndColor(mode, startColor, endColor);
    changeToColor(startColor, endColor, colorSchemeAnimiDuration);
}

void customButton::enterEvent(QEvent *)
{
    if(!(type == DYNAMIC || type == DYNAMIC_RADIUS)) return;
    QColor enterColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightModeHoveringColor : darkModeHoveringColor);
    changeToColor(m_color, enterColor, hoverAnimiDuration);
}

void customButton::leaveEvent(QEvent*){
    if(!(type == DYNAMIC || type == DYNAMIC_RADIUS)) return;
    QColor leaveColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightmodeColor : darkmodeColor);
    changeToColor(m_color, leaveColor, hoverAnimiDuration);
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
    if(type == CHECKABLE || type == CHECKABLE_RADIUS)
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
    else if(type == DYNAMIC || type == DYNAMIC_RADIUS)
    {
        CellWidgetGlobalInterface::setColor(color);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
    }
    else if(type == STATIC || type == STATIC_RADIUS)
    {
        CellWidgetGlobalInterface::setColor(color);
        QColor hoverColor = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? brightModeHoverColor : darkModeHoverColor);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(hoverColor.red()).arg(hoverColor.green()).arg(hoverColor.blue()));
    }
}
