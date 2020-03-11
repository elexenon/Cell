// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customButton.h"
#include "../../CellCore/CellVariant.h"
#include "../../CellCore/Kits/CellUtility.h"

//#define NDEBUG
#include <cassert>

customButton::customButton(ButtonType type, QWidget *parent):
    QPushButton(parent),
    mType(type),
    brightCheckedColor(nullptr),  darkCheckedColor(nullptr),
    brightHoveringColor(nullptr), darkHoveringColor(nullptr),
    brightHoverColor(nullptr),    darkHoverColor(nullptr)
{
    init();
    setEventConnections();
}

void customButton::init()
{
    setFlat(true);
    if((mType & Static) == Static){
        brightHoverColor = new QColor;
        darkHoverColor   = new QColor;
    }
    else if((mType & Dynamic) == Dynamic){
        brightHoveringColor = new QColor;
        darkHoveringColor   = new QColor;
    }
    else{
        setCheckable(true);
        brightCheckedColor = new QColor;
        darkCheckedColor   = new QColor;
    }
}

void customButton::setEventConnections()
{
    connect(this, &QPushButton::toggled, [=](bool checked){
        if((mType & Checkable) == Checkable){
            checked ? setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ? *brightCheckedColor : *darkCheckedColor):
                      setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
        }
    });
}

void customButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(mColor);

    QRect rect = this->rect();
    if((mType & Radius) == Radius){
        QPen pen(QColor(180, 180, 180), 1);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);
        painter.drawRoundedRect(rect, Cell::FrameRadius, Cell::FrameRadius);
    }
    else{
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect);
    }
    if(naviVerBar && isChecked()){
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(CellVariant(Cell::CellThemeColor::NavyBlue).toColor()));
        painter.drawRect(this->width() - 5, 1, 5, this->height()-2);
    }
    e->accept();
}

void customButton::changeToColor(const QColor &startColor, const QColor &targetColor, int duration){
    CellWidgetGlobalInterface::switchMode == Cell::SwitchMode::Instant ?
    setColor(targetColor):
    CellUiGlobal::setPropertyAnimation(animi, this, "color",
                                       startColor, targetColor, duration,
                                       CellWidgetGlobalInterface::easingCurve);
}
// Not using the default implementation
// of base class CellWidgetGlobalInterface
void customButton::setColorScheme(Cell::ColorScheme mode){
    CellWidgetGlobalInterface::setColorScheme(mode);
}

void customButton::enterEvent(QEvent *)
{
    if((mType & Static) == Static)
        setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ?
                     *brightHoverColor :
                     *darkHoverColor);
    else if((mType & Dynamic) == Dynamic){
        QColor *enterColor = (CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ?
                                  brightHoveringColor :
                                  darkHoveringColor);
        changeToColor(mColor, *enterColor, hoverAnimiDuration);
    }else{
        if(!isChecked())
            setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ?
                         *brightCheckedColor :
                         *darkCheckedColor);
    }
}

void customButton::leaveEvent(QEvent*){
    if((mType & Static) == Static)
        setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ?
                     brightmodeColor :
                     darkmodeColor);
    else if((mType & Dynamic) == Dynamic){
        QColor leaveColor = (CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ?
                                 brightmodeColor :
                                 darkmodeColor);
        changeToColor(mColor, leaveColor, hoverAnimiDuration);
    }else{
        if(!isChecked())
            setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ?
                         brightmodeColor :
                         darkmodeColor);
    }
}

void customButton::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    update();
}

void customButton::setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor,
                                         QColor &endColor)
{
    startColor = mColor;
    if((mType & Checkable) == Checkable){
        endColor = isChecked() ? (mode == Cell::ColorScheme::Dark ? *darkCheckedColor : *brightCheckedColor):
                                 (mode == Cell::ColorScheme::Dark ? darkmodeColor : brightmodeColor);
    }
    else{
        endColor = mode == Cell::ColorScheme::Dark ? darkmodeColor : brightmodeColor;
    }
}
// Setters.
void customButton::setBrightCheckedColor(const CellVariant &color)
{
    assert(brightCheckedColor);
    *brightCheckedColor = color.toColor();
}

void customButton::setDarkCheckedColor(const CellVariant &color)
{
    assert(brightCheckedColor);
    *darkCheckedColor = color.toColor();
}

void customButton::setBrightHoveringColor(const CellVariant &color)
{
    assert(brightHoveringColor);
    *brightHoveringColor = color.toColor();
}

void customButton::setDarkHoveringColor(const CellVariant &color)
{
    assert(brightHoveringColor);
    *darkHoveringColor = color.toColor();
}

void customButton::setBrightHoverColor(const CellVariant &color)
{
    assert(brightHoverColor);
    *brightHoverColor = color.toColor();
}

void customButton::setDarkHoverColor(const CellVariant &color)
{
    assert(brightHoverColor);
    *darkHoverColor = color.toColor();
}
