// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customButton.h"
#include "../../CellCore/CellVariant.h"
#include "../../CellCore/Kits/CellUtility.h"

customButton::customButton(customButton::Type type, QWidget *parent):
    QPushButton(parent),
    mType(type)
{
    setBaseQss("");
}

void customButton::setBaseQss(const QString &qss)
{
    (void)qss;
    QString qssFileName;
    switch(mType){
    case Static:
        qssFileName = "CustomButtonStatic.css";
        setFlat(true);
        break;
    case Dynamic:
        qssFileName = "CustomButtonDynamic.css";
        break;
    case Checkable:
        setCheckable(true);
        qssFileName = "CustomButtonCheckable.css";
        break;
    case StaticRadius:
        qssFileName = "CustomButtonStaticRadius.css";
        setFlat(true);
        break;
    case DynamicRadius:
        qssFileName = "CustomButtonDynamicRadius.css";
        break;
    case CheckableRadius:
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
    m_mode = Cell::ColorScheme::Dark;
    QColor startColor;
    QColor endColor;
    setAnimiStartEndColor(mode, startColor, endColor);
    changeToColor(startColor, endColor, colorSchemeAnimiDuration);
}

void customButton::enterEvent(QEvent *)
{
    if(!(mType == Dynamic || mType == DynamicRadius)) return;
    QColor enterColor = (m_mode == Cell::ColorScheme::Bright ? brightModeHoveringColor : darkModeHoveringColor);
    changeToColor(m_color, enterColor, hoverAnimiDuration);
}

void customButton::leaveEvent(QEvent*){
    if(!(mType == Dynamic || mType == DynamicRadius)) return;
    QColor leaveColor = (m_mode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
    changeToColor(m_color, leaveColor, hoverAnimiDuration);
}

void customButton::setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor,
                                         QColor &endColor)
{
    if(mType == Checkable)
    {
        if(mode == Cell::ColorScheme::Dark){
            if(!isChecked()){
                startColor = m_color;
                endColor = darkmodeColor;
            }else{
                startColor = brightModeCheckedColor;
                endColor = darkModeCheckedColor;
                m_color = darkmodeColor;
            }
        }else if(mode == Cell::ColorScheme::Bright){
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
    else if(mType == Dynamic || mType == Static)
    {
        startColor = color();
        endColor = (m_mode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
    }
}

void customButton::setColor(const QColor &color)
{
    if(mType == Checkable || mType == CheckableRadius)
    {
        if(!isChecked()){
            CellWidgetGlobalInterface::setColor(color);
            QColor checkedColor = (m_mode == Cell::ColorScheme::Bright ? brightModeCheckedColor : darkModeCheckedColor);
            setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                          .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue())
                          .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue()));
        }else
            setStyleSheet(BASEQSS.arg(m_color.red()).arg(m_color.green()).arg(m_color.blue())
                          .arg(color.red()).arg(color.green()).arg(color.blue())
                          .arg(color.red()).arg(color.green()).arg(color.blue()));
    }
    else if(mType == Dynamic || mType == DynamicRadius)
    {
        CellWidgetGlobalInterface::setColor(color);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
    }
    else if(mType == Static || mType == StaticRadius)
    {
        CellWidgetGlobalInterface::setColor(color);
        QColor hoverColor = (m_mode == Cell::ColorScheme::Bright ? brightModeHoverColor : darkModeHoverColor);
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
