// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/Kits/customFrame.h"

#include <QDebug>

customFrame::customFrame(const QString &qss, QWidget *parent):
    QFrame(parent),
    BASEQSS(qss)
{}

const QColor customFrame::color() const
{
    return m_color;
}

void customFrame::setColor(const QColor &color)
{
    m_color = color;
    setStyleSheet(BASEQSS.arg(color.red()).arg(color.green()).arg(color.blue()));
}
