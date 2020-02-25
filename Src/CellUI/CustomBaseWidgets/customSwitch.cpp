// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customSwitch.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/CellVariant.h"

customSwitch::customSwitch(QWidget *parent):
    QWidget(parent),
    triggerColor(Qt::white),
    paddingColor(QColor(235,235,235))
{
    init();
}

void customSwitch::init()
{
    setCursor(Qt::PointingHandCursor);
    setFixedSize(50, triggerDiam);
    animi.setTargetObject(this);
    animi.setPropertyName("triggerOffset");
    animi.setEasingCurve(QEasingCurve::InOutSine);
    animi.setDuration(150);
}

void customSwitch::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the padding area.
    QPainterPath path;
    path.addRoundedRect(QRectF(margin, margin, this->width() - 2*margin, this->height() - 2*margin),
                        paddingRadius, paddingRadius);

    if(this->isChecked){
        QLinearGradient gradient(-7, this->height()/2, this->width(), this->height()/2);
        gradient.setColorAt(0.0, QColor(235, 235, 235));
        gradient.setColorAt(1.0, QColor(26, 96, 134));
        painter.setBrush(gradient);
    }
    else
        painter.setBrush(paddingColor);
    painter.setPen(QPen(QColor(60,60,60),0.2));
    painter.drawPath(path.simplified());

    // Draw area of trigger.
    painter.setPen(Qt::NoPen);
    painter.setBrush(triggerColor);
    painter.setOpacity(this->isEnabled() ? 1 : 0.6);
    painter.drawEllipse(triggerPosOffset, 0, triggerDiam, triggerDiam);
}

void customSwitch::mousePressEvent(QMouseEvent *event)
{
    if(!isEnabled()) return;
    if(event->buttons() & Qt::LeftButton)
        event->accept();
    else
        event->ignore();
}

void customSwitch::mouseReleaseEvent(QMouseEvent *event)
{
    if(!isEnabled()) return;
    if((event->type() == QMouseEvent::MouseButtonRelease) && (event->button() == Qt::LeftButton)){
        event->accept();
        switchTrigger();
        isChecked = !isChecked;
        emit clicked(isChecked);
        return;
    }
    event->ignore();
}

void customSwitch::switchTrigger()
{
    qreal sValue = this->isChecked ? this->width() - triggerDiam : 0;
    qreal eValue = this->isChecked ? 0 : this->width() - triggerDiam;
    animi.setStartValue(sValue);
    animi.setEndValue(eValue);
    animi.start(QAbstractAnimation::KeepWhenStopped);
}

void customSwitch::setChecked(bool checked)
{
    if(checked != isChecked)
        switchTrigger();
    isChecked = checked;
}
