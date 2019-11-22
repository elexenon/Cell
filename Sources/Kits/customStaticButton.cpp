// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/kits/customStaticButton.h"
#include "Headers/Kits/cell_util.h"

using namespace CELL_UTIL;

customStaticButton::customStaticButton(QWidget *parent):
    QPushButton(parent),
    BASEQSS(LITERAL::QSS_CUSTOMBUTTON_STATIC)
{}

void customStaticButton::setBrightModeCheckedUncheckedColor(const QColor &c, const QColor &u){
    brightModeCheckedColor = c; brightModeLeaveColor = u;
}

void customStaticButton::setDarkModeCheckedUncheckedColor(const QColor &c, const QColor &u){
    darkModeCheckedColor = c; darkModeLeaveColor = u;
}

void customStaticButton::Init(){
    m_colorScheme = COLOR_SCHEME::_BRIGHT;
    currColor = brightModeLeaveColor;
    setStyleSheet(BASEQSS.arg(currColor.red()).arg(currColor.green()).arg(currColor.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue()));
#ifdef CELL_DEBUG
    qDebug() << styleSheet();
    qDebug() << currColor;
#endif
}

void customStaticButton::setColorScheme(COLOR_SCHEME mode)
{
    if(mode == m_colorScheme) return;
    QColor startColor;
    QColor endColor;
    if(mode == COLOR_SCHEME::_DARK){
        m_colorScheme = COLOR_SCHEME::_DARK;
        if(!isChecked()){
            startColor = currColor;
            endColor = darkModeLeaveColor;
        }else{
            startColor = brightModeCheckedColor;
            endColor = darkModeCheckedColor;
            currColor = darkModeLeaveColor;
        }
        TOOLS::setPropertyAnimation({animi},
                                     "color",
                                     startColor,
                                     endColor,
                                     CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    }else if(mode == COLOR_SCHEME::_BRIGHT){
        m_colorScheme = COLOR_SCHEME::_BRIGHT;
        if(!isChecked()){
            startColor = currColor;
            endColor = brightModeLeaveColor;
        }else{
            startColor = darkModeCheckedColor;
            endColor = brightModeCheckedColor;
            currColor = brightModeLeaveColor;
        }
        TOOLS::setPropertyAnimation({animi},
                                     "color",
                                     startColor,
                                     endColor,
                                     CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
        {this},nullptr);
    }
}

const QColor customStaticButton::color() const
{
    return currColor;
}

void customStaticButton::setColor(const QColor &color)
{
    if(!isChecked()){
        currColor = color;
        QColor checkedColor = (m_colorScheme == COLOR_SCHEME::_BRIGHT ? brightModeCheckedColor : darkModeCheckedColor);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue())
                      .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue()));
    }else
        setStyleSheet(BASEQSS.arg(currColor.red()).arg(currColor.green()).arg(currColor.blue())
                      .arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(color.red()).arg(color.green()).arg(color.blue()));
}
