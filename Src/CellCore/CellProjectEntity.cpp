// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QDateTime>
#include <QJsonObject>
#include "CellProjectEntity.h"
#include "Kits/CellGlobalMacros.h"
#define CELL_DEBUG

CellProjectEntity::CellProjectEntity()
{
    mSize = 1024;
    QDateTime curr = QDateTime::currentDateTime();
    mModifiedTime = curr.toString("yyyy-MM-dd-hh:mm");
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

CellProjectEntity::CellProjectEntityType CellProjectEntity::getType(const QString &type)
{
    if(type == CMPSTR("Cell DeepLearning")) return _CELLDEEPLEARNING;
    else if(type == CMPSTR("基于Cell DeepLearning的地震预测")) return _PREDICTEARTHQUAKE;
    else if(type == CMPSTR("Empty File")) return _EMPTY;
    else if(type == CMPSTR("C++ File")) return _CPP;
    return _PYTHON;
}

void CellProjectEntity::print()
{
    qDebug() << CHAR2STR("Project:")
             << mName
             << mModifiedTime
             << mPath;
}

void CellProjectEntity::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("modifiedTime") && json["modifiedTime"].isString())
        mModifiedTime = json["modifiedTime"].toString();

    if (json.contains("type") && json["type"].isString())
        mType = getType(json["type"].toString());

    if (json.contains("path") && json["path"].isString())
        mPath = json["path"].toString();

    if (json.contains("code") && json["code"].isString())
        mCode = json["code"].toString();

    mSize = json["size"].toInt();
}

void CellProjectEntity::write(QJsonObject &json)
{
    json["Name"] = mName;
    json["modifiedTime"] = mModifiedTime;
    json["size"] = mSize;
    json["type"] = getType(mType);
    json["path"] = mPath;
    json["code"] = mCode;
}
