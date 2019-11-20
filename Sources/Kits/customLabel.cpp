// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/Kits/customLabel.h"
#include <QStyleOption>
#include <QStylePainter>

customLabel::customLabel(const QString &qss, QWidget *parent):
    QLabel(parent),
    BASEQSS(qss)
{}

const QColor customLabel::color() const
{
    return m_color;
}

void customLabel::setColor(const QColor color)
{
    m_color = color;
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked();
}
