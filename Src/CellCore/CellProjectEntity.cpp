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
    m_size = 1024;
    QDateTime curr = QDateTime::currentDateTime();
    m_modifiedTime = curr.toString("yyyy-MM-dd");
}

const QString CellProjectEntity::getType(CellProjectEntity::CellProjectEntityType type)
{
    QString tmp;
    switch(type){
    case CellProjectEntity::_CELLDEEPLEARNING:
        tmp = CHAR2STR("Cell DeepLearning");
        break;
    case CellProjectEntity::_PREDICTEARTHQUAKE:
        tmp = CHAR2STR("基于Cell DeepLearning的地震预测");
        break;
    case CellProjectEntity::_EMPTY:
        tmp = CHAR2STR("Empty File");
        break;
    case CellProjectEntity::_CPP:
        tmp = CHAR2STR("C++ File");
        break;
    case CellProjectEntity::_PYTHON:
        tmp = CHAR2STR("Python File");
        break;
    }
    return tmp;
}

void CellProjectEntity::print()
{
    qDebug() << CHAR2STR("Project:")
             << m_name
             << m_modifiedTime
             << m_path;
}
