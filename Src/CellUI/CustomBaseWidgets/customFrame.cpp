// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customFrame.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QDebug>

customFrame::customFrame(Type type, QWidget *parent):
    QFrame(parent),
    mType(type)
{
    init();
    setEventConnections();
}

void customFrame::init()
{}

void customFrame::setEventConnections()
{}

void customFrame::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    update();
}

void customFrame::changeToColor(const QColor& startColor, const QColor &targetColor, int duration){
    CellWidgetGlobalInterface::switchMode == Cell::SwitchMode::Instant ?
    setColor(targetColor):
    CellUiGlobal::setPropertyAnimation(animi, this, "color",
                                       startColor, targetColor, duration,
                                       CellWidgetGlobalInterface::easingCurve);
}

void customFrame::paintEvent(QPaintEvent *e)
{
    e->accept();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(mColor);

    QRect rect = this->rect();
    if(mType == Type::Radius){
        QPen pen(QColor(180, 180, 180), 1);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawRoundedRect(rect, Cell::FrameRadius, Cell::FrameRadius);
    }
    else{
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect);
    }
}

void customFrame::setColorScheme(Cell::ColorScheme mode){
    CellWidgetGlobalInterface::setColorScheme(mode);
}
