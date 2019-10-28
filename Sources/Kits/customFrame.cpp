// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../../Headers/Kits/customFrame.h"
#include <QDebug>

customFrame::customFrame(WINDOW_TYPE type, QWidget *parent):
    QFrame(parent)
   ,m_type(type)
   ,m_color(QColor(255, 255, 255))
{}

const QColor customFrame::color() const
{
    return m_color;
}

void customFrame::setColor(const QColor color)
{
    m_color = color;
    QString qss;
    m_type == WINDOW_TYPE::_CHILD ?
        qss=QString("QFrame{border-radius:5px; background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue())
       :qss=QString("QFrame{background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue());
    setStyleSheet(qss);
}
