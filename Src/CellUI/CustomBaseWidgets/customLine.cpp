// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customLine.h"

customLine::customLine(const QString &qss, QWidget *parent, const customLine::LINESHAPE &shape):
    customFrame(qss,parent),
    shape(shape)
{
    Init();
}

void customLine::Init()
{
    auto targetShape = (shape == _HORIZONTAL ? QFrame::HLine : QFrame::VLine);
    setFrameShape(targetShape);
    setFrameShadow(QFrame::Sunken);
};
