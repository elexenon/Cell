// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customButton.h"
#include "../../CellCore/CellVariant.h"
#include "../../CellCore/Kits/CellUtility.h"

//#define NDEBUG

customButton::customButton(ButtonType type, QWidget *parent):
    QPushButton(parent),
    mType(type),
    brightCheckedColor(nullptr),
    darkCheckedColor(nullptr),
    mDrawMark(false),
    mDrawFocusEdge(false),
    brightHoveringColor(nullptr),
    darkHoveringColor(nullptr),
    brightHoverColor(nullptr),
    darkHoverColor(nullptr)
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

customButton::~customButton()
{
    CellSafeDelete(brightHoverColor)
    CellSafeDelete(darkHoverColor)
    CellSafeDelete(brightHoveringColor)
    CellSafeDelete(darkHoveringColor)
    CellSafeDelete(brightCheckedColor)
    CellSafeDelete(darkCheckedColor)
}

void customButton::setEventConnections()
{
    connect(this, &QPushButton::toggled, [=](bool checked){
        if((mType & Checkable) == Checkable){
            checked ? setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ? *brightCheckedColor : *darkCheckedColor):
                      setColor(CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright ? brightmodeColor : darkmodeColor);
            if(mDrawFocusEdge && isCheckable()) updateFocusEdge();
        }
    });
}

void customButton::paintEvent(QPaintEvent *e)
{
    QColor navyBlue(CellVariant(Cell::CellThemeColor::NavyBlue).toColor());
    QRect rect = this->rect();
    QPen pen;
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    QBrush brush(mColor);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush);

    if((mType & Radius) == Radius){
        pen.setColor(QColor(180, 180, 180));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawRoundedRect(rect, Cell::FrameRadius, Cell::FrameRadius);
    }
    else{
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect);
    }
    if(mDrawMark && isChecked()){
        static int markWidth = 5;
        brush.setColor(navyBlue);
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawRect(this->width() - markWidth, 1, markWidth, this->height() - 2);
    }
    if(mDrawFocusEdge && isCheckable()){
        navyBlue.setAlphaF(1.0 - mFocusEdgeOffset*0.1);
        pen.setColor(navyBlue);
        pen.setWidth(4);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        (mType & Radius) == Radius ?
        painter.drawRoundedRect(QRect(rect.x() + mFocusEdgeOffset, rect.y() + mFocusEdgeOffset,
                                      rect.width() - 2*mFocusEdgeOffset, rect.height() -2*mFocusEdgeOffset),
                                Cell::FrameRadius + 1, Cell::FrameRadius+1):
        painter.drawRect(QRect(rect.x() + mFocusEdgeOffset, rect.y() + mFocusEdgeOffset,
                                      rect.width() - 2*mFocusEdgeOffset, rect.height() -2*mFocusEdgeOffset));
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

void customButton::updateFocusEdge()
{
    static qreal maxOffset = 10.0;
    qreal targetOffset = isChecked() ? 0.0 : maxOffset;
    CellWidgetGlobalInterface::switchMode == Cell::SwitchMode::Instant ?
    setFocusEdgeOffset(targetOffset):
    CellUiGlobal::setPropertyAnimation(animi, this, "focusEdgeOffset",
                                       mFocusEdgeOffset, targetOffset, 180,
                                       CellWidgetGlobalInterface::easingCurve);
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
