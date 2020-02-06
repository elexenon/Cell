// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QDateTime>
#include "CellProjectEntity.h"
#define CELL_DEBUG

CellProjectEntity::CellProjectEntity()
{
    QDateTime curr = QDateTime::currentDateTime();
    modifiedTime = curr.toString("yyyy-MM-dd");
}
