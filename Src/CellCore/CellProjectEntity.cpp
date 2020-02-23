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
    case CellProjectEntity::CellDeepLearning:
        tmp = "Cell DeepLearning";
        break;
    case CellProjectEntity::PredictEarthquake:
        tmp = "基于Cell DeepLearning的地震预测";
        break;
    case CellProjectEntity::Empty:
        tmp = "Empty File";
        break;
    case CellProjectEntity::CPP:
        tmp = "C++ File";
        break;
    case CellProjectEntity::Python:
        tmp = "Python File";
        break;
    }
    return tmp;
}

CellProjectEntity::CellProjectEntityType CellProjectEntity::getType(const QString &type)
{
    if(type == CMPSTR("Cell DeepLearning")) return CellDeepLearning;
    else if(type == CMPSTR("基于Cell DeepLearning的地震预测")) return PredictEarthquake;
    else if(type == CMPSTR("Empty File")) return Empty;
    else if(type == CMPSTR("C++ File")) return CPP;
    return Python;
}

void CellProjectEntity::print()
{
    CELL_DEBUG("CellProjectEntity") << "SelfPrint:\n"
                                    << mName         << endl
                                    << mModifiedTime << endl
                                    << mType         << endl
                                    << mPath         << endl;
}

void CellProjectEntity::read(const QJsonObject &json)
{
    if (json.contains("Name") && json["Name"].isString())
        mName = json["Name"].toString();

    if (json.contains("ModifiedTime") && json["ModifiedTime"].isString())
        mModifiedTime = json["ModifiedTime"].toString();

    if (json.contains("Type") && json["Type"].isString())
        mType = getType(json["Type"].toString());

    if (json.contains("Path") && json["Path"].isString())
        mPath = json["Path"].toString();

    if (json.contains("Code") && json["Code"].isString())
        mCode = json["Code"].toString();
}

void CellProjectEntity::write(QJsonObject &json)
{
    json["Name"] = mName;
    json["ModifiedTime"] = mModifiedTime;
    json["Type"] = getType(mType);
    json["Path"] = mPath;
    json["Code"] = mCode;
}
