// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../../Headers/Kits/customFrame.h"
#include <QDebug>

customFrame::customFrame(FRAME_TYPE type, QWidget *parent):
    QFrame(parent)
   ,m_type(type)
{}

const QColor customFrame::color() const
{
    return m_color;
}

void customFrame::setColor(const QColor color)
{
    m_color = color;
    QString qss;
    using F_T = FRAME_TYPE;
    switch(m_type){
        case F_T::_OPTIONBLOCK:
            qss=QString("QFrame{border-radius:5px; background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue());
        break;

        case F_T::_REGULAR:
            qss=QString("QFrame{background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue());
        break;
    }
    setStyleSheet(qss);
}
