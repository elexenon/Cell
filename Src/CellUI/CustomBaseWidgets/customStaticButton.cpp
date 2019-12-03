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
    BASEQSS(Cell_Const::QSS_CUSTOMBUTTON_STATIC)
{}

void customStaticButton::setBrightModeCheckedUncheckedColor(const QColor &c, const QColor &u){
    brightModeCheckedColor = c; brightModeLeaveColor = u;
}

void customStaticButton::setDarkModeCheckedUncheckedColor(const QColor &c, const QColor &u){
    darkModeCheckedColor = c; darkModeLeaveColor = u;
}

void customStaticButton::Init(){
    m_colorScheme = CellGlobal::COLOR_SCHEME::_BRIGHT;
    currColor = brightModeLeaveColor;
    setStyleSheet(BASEQSS.arg(currColor.red()).arg(currColor.green()).arg(currColor.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue())
                  .arg(brightModeCheckedColor.red()).arg(brightModeCheckedColor.green()).arg(brightModeCheckedColor.blue()));
#ifdef CELL_DEBUG
    qDebug() << styleSheet();
    qDebug() << currColor;
#endif
}

void customStaticButton::setColorScheme(CellGlobal::COLOR_SCHEME mode)
{
    if(mode == m_colorScheme) return;
    QColor startColor;
    QColor endColor;
    if(mode == CellGlobal::COLOR_SCHEME::_DARK){
        m_colorScheme = CellGlobal::COLOR_SCHEME::_DARK;
        if(!isChecked()){
            startColor = currColor;
            endColor = darkModeLeaveColor;
        }else{
            startColor = brightModeCheckedColor;
            endColor = darkModeCheckedColor;
            currColor = darkModeLeaveColor;
        }
        CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                     startColor,
                                     endColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    }else if(mode == CellGlobal::COLOR_SCHEME::_BRIGHT){
        m_colorScheme = CellGlobal::COLOR_SCHEME::_BRIGHT;
        if(!isChecked()){
            startColor = currColor;
            endColor = brightModeLeaveColor;
        }else{
            startColor = darkModeCheckedColor;
            endColor = brightModeCheckedColor;
            currColor = brightModeLeaveColor;
        }
        CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                     startColor,
                                     endColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
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
        QColor checkedColor = (m_colorScheme == CellGlobal::COLOR_SCHEME::_BRIGHT ? brightModeCheckedColor : darkModeCheckedColor);
        setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue())
                      .arg(checkedColor.red()).arg(checkedColor.green()).arg(checkedColor.blue()));
    }else
        setStyleSheet(BASEQSS.arg(currColor.red()).arg(currColor.green()).arg(currColor.blue())
                      .arg(color.red()).arg(color.green()).arg(color.blue())
                      .arg(color.red()).arg(color.green()).arg(color.blue()));
}
