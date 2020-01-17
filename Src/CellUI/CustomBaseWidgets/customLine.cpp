// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customLine.h"

customLine::customLine(const QString &qss, QWidget *parent, const CellUiGlobal::LINE_TYPE &shape):
    customFrame(qss,parent),
    shape(shape)
{
    Init();
}

void customLine::Init()
{
    auto targetShape = (shape == CellUiGlobal::LINE_TYPE::HLine ? QFrame::HLine : QFrame::VLine);
    setFrameShape(targetShape);
    setFrameShadow(QFrame::Sunken);
};
