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

CellProjectEntity::CellProjectEntity(const QString &name, const CellProjectEntity::CellProjectEntityType &type):
    type(type),
    name(name)
{
    QDateTime curr = QDateTime::currentDateTime();
    creationTime = curr.toString("yyyy-MM-dd");
#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "NEW PROJECT";
    qDebug() << "ProjectName:" << name;
    qDebug() << "ProjectType:" << type;
    qDebug() << "CreationTime:" << creationTime;
    qDebug() << "--------------------------\n";
#endif
}
