// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customButton.h"
#include "../../CellCore/CellVariant.h"

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
    CellUiGlobal::loader.setFileName(qssFileName);
    BASEQSS = CellUiGlobal::loader.content();
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

void customButton::setColorScheme(Cell::ColorScheme mode)
{
    if(mode == m_mode) return;
    m_mode = Cell::ColorScheme::_DARK;
    QColor startColor;
    QColor endColor;
    setAnimiStartEndColor(mode, startColor, endColor);
    changeToColor(startColor, endColor, colorSchemeAnimiDuration);
}

void customButton::enterEvent(QEvent *)
{
    if(!(type == DYNAMIC || type == DYNAMIC_RADIUS)) return;
    QColor enterColor = (m_mode == Cell::ColorScheme::_BRIGHT ? brightModeHoveringColor : darkModeHoveringColor);
    changeToColor(m_color, enterColor, hoverAnimiDuration);
}

void customButton::leaveEvent(QEvent*){
    if(!(type == DYNAMIC || type == DYNAMIC_RADIUS)) return;
    QColor leaveColor = (m_mode == Cell::ColorScheme::_BRIGHT ? brightmodeColor : darkmodeColor);
    changeToColor(m_color, leaveColor, hoverAnimiDuration);
}

void customButton::setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor,
                                         QColor &endColor)
{
    if(type == CHECKABLE)
    {
        if(mode == Cell::ColorScheme::_DARK){
            if(!isChecked()){
                startColor = m_color;
                endColor = darkmodeColor;
            }else{
                startColor = brightModeCheckedColor;
                endColor = darkModeCheckedColor;
                m_color = darkmodeColor;
            }
        }else if(mode == Cell::ColorScheme::_BRIGHT){
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
        endColor = (m_mode == Cell::ColorScheme::_BRIGHT ? brightmodeColor : darkmodeColor);
    }
}

void customButton::setColor(const QColor &color)
{
    if(type == CHECKABLE || type == CHECKABLE_RADIUS)
    {
        if(!isChecked()){
            CellWidgetGlobalInterface::setColor(color);
            QColor checkedColor = (m_mode == Cell::ColorScheme::_BRIGHT ? brightModeCheckedColor : darkModeCheckedColor);
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
        QColor hoverColor = (m_mode == Cell::ColorScheme::_BRIGHT ? brightModeHoverColor : darkModeHoverColor);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(hoverColor.red()).arg(hoverColor.green()).arg(hoverColor.blue()));
    }
}

void customButton::setBrightModeCheckedColor(const CellVariant &color)
{
    brightModeCheckedColor = color.toColor();
}

void customButton::setDarkModeCheckedColor(const CellVariant &color)
{
    darkModeCheckedColor = color.toColor();
}

void customButton::setBrightModeHoveringColor(const CellVariant &color)
{
    brightModeHoveringColor = color.toColor();
}

void customButton::setDarkModeHoveringColor(const CellVariant &color)
{
    darkModeHoveringColor = color.toColor();
}

void customButton::setBrightModeHoverColor(const CellVariant &color)
{
    brightModeHoverColor = color.toColor();
}

void customButton::setDarkModeHoverColor(const CellVariant &color)
{
    darkModeHoverColor = color.toColor();
}
