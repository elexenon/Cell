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

customButton::customButton(customButton::Type type, QWidget *parent):
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
    switch(mType){
    case Static:
    case StaticRadius:
        brightHoverColor = new QColor;
        darkHoverColor   = new QColor;
        break;
    case Dynamic:
    case DynamicRadius:
        brightHoveringColor = new QColor;
        darkHoveringColor   = new QColor;
        break;
    case Checkable:
    case CheckableRadius:
        setCheckable(true);
        brightCheckedColor = new QColor;
        darkCheckedColor   = new QColor;
        break;
    }
}

void customButton::setEventConnections()
{
    connect(this, &QPushButton::clicked, [=]{
        if(mType == Type::Checkable || mType == Type::CheckableRadius){
            isChecked() ? setColor(mMode == Cell::ColorScheme::Bright ? *brightCheckedColor : *darkCheckedColor):
                          setColor(mMode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
        }
    });
}

void customButton::paintEvent(QPaintEvent *e)
{
    e->accept();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(mColor);

    QRect rect = this->rect();
    if(mType == Type::StaticRadius || mType == Type::DynamicRadius || mType == Type::CheckableRadius){
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
        painter.drawRect(0, 0, 5, this->height());
    }
}

void customButton::changeToColor(const QColor &startColor, const QColor &targetColor, int duration){
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
    switch(mType){
    case Static:
    case StaticRadius:
        setColor(mMode == Cell::ColorScheme::Bright ? *brightHoverColor : *darkHoverColor);
        break;
    case Checkable:
    case CheckableRadius:
        if(!isChecked())
            setColor(mMode == Cell::ColorScheme::Bright ? *brightCheckedColor : *darkCheckedColor);
        break;
    case Dynamic:
    case DynamicRadius:
        QColor *enterColor = (mMode == Cell::ColorScheme::Bright ? brightHoveringColor : darkHoveringColor);
        changeToColor(mColor, *enterColor, hoverAnimiDuration);
        break;
    }
}

void customButton::leaveEvent(QEvent*){
    switch(mType){
    case Static:
    case StaticRadius:
        setColor(mMode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
        break;
    case Checkable:
    case CheckableRadius:
        if(!isChecked())
            setColor(mMode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
        break;
    case Dynamic:
    case DynamicRadius:
        QColor leaveColor = (mMode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
        changeToColor(mColor, leaveColor, hoverAnimiDuration);
        break;
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
    switch(mType){
    case Checkable:
    case CheckableRadius:
        endColor = isChecked() ? (mode == Cell::ColorScheme::Dark ? *darkCheckedColor : *brightCheckedColor):
                                 (mode == Cell::ColorScheme::Dark ? darkmodeColor : brightmodeColor);
        break;
    case Static:
    case Dynamic:
    case StaticRadius:
    case DynamicRadius:
        endColor = mode == Cell::ColorScheme::Dark ? darkmodeColor : brightmodeColor;
        break;
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
