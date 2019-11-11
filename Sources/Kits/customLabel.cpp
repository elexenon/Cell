// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/Kits/customLabel.h"

customLabel::customLabel(QWidget *parent):
    QLabel(parent)
{}

const QColor customLabel::color() const
{
    return m_color;
}

void customLabel::setColor(const QColor color)
{
    m_color = color;
    QString qss=QString("QLabel{color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue());
    setStyleSheet(qss);
}
