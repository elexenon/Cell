// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QDateTime>
#include "CellProjectEntity.h"
#include "Kits/CellGlobalMacros.h"
#define CELL_DEBUG

CellProjectEntity::CellProjectEntity()
{
    QDateTime curr = QDateTime::currentDateTime();
    m_modifiedTime = curr.toString("yyyy-MM-dd");
}

void CellProjectEntity::print()
{
    qDebug() << CHAR2STR("Project:")
             << m_name
             << m_modifiedTime
             << m_path;
}
