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

CellProjectEntity::CellProjectEntity()
{
    QDateTime curr = QDateTime::currentDateTime();
    mModifiedTime = curr.toString("yyyy-MM-dd-hh:mm");
}

const QString CellProjectEntity::getType(CellProjectEntityType type)
{
    QString tmp;
    switch(type){
    case CellProjectEntity::_CELLDEEPLEARNING:
        tmp = "Cell DeepLearning";
        break;
    case CellProjectEntity::_PREDICTEARTHQUAKE:
        tmp = "基于Cell DeepLearning的地震预测";
        break;
    case CellProjectEntity::_EMPTY:
        tmp = "Empty File";
        break;
    case CellProjectEntity::_CPP:
        tmp = "C++ File";
        break;
    case CellProjectEntity::_PYTHON:
        tmp = "Python File";
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
    CELL_DEUBG("CellProjectEntity") << "SelfPrint:\n"
                                    << mName         << endl
                                    << mModifiedTime << endl
                                    << mType         << endl
                                    << mPath         << endl;
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
}

void CellProjectEntity::write(QJsonObject &json)
{
    json["name"] = mName;
    json["modifiedTime"] = mModifiedTime;
    json["type"] = getType(mType);
    json["path"] = mPath;
    json["code"] = mCode;
}
