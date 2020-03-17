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
#include "../../CellCore/Kits/CellUtility.h"

CellProjectEntity::CellProjectEntity() noexcept
{
    mModifiedTime = CellUiGlobal::getProjectTime();
}

CellProjectEntity::CellProjectEntity(const QString &name, const QString &time,
                                     ProjectType type, const QString &path) noexcept:
    mName(name),mModifiedTime(time),mType(type),mPath(path){}

const QString CellProjectEntity::getType(ProjectType type)
{
    QString tmp;
    switch(type){
    case CellProjectEntity::CellDeepLearning:
        tmp = "Cell DeepLearning";
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
    case CellProjectEntity::ImageClassify:
        tmp = "图像分类";
        break;
    case CellProjectEntity::ObjectDetect:
        tmp = "对象探测";
        break;
    case CellProjectEntity::PredictEarthquake:
        tmp = "基于Cell DeepLearning的地震预测";
        break;
    }
    return tmp;
}

CellProjectEntity::ProjectType CellProjectEntity::getType(const QString &type)
{
    if(type == CMPSTR("Cell DeepLearning")) return CellDeepLearning;
    else if(type == CMPSTR("Empty File")) return Empty;
    else if(type == CMPSTR("C++ File")) return CPP;
    else if(type == CMPSTR("Python File")) return Python;
    else if(type == CMPSTR("图像分类")) return ImageClassify;
    else if(type == CMPSTR("对象探测")) return ObjectDetect;
    return PredictEarthquake;
}

CellProjectEntity CellProjectEntity::convert(const QList<QStandardItem*> &items)
{
    return CellProjectEntity(items[0]->text(), items[1]->text(),
                             getType(items[2]->text()), items[3]->text());
}

bool CellProjectEntity::validEntity(CellProjectEntity &entity)
{
    QRegExp exp(CHAR2STR("[<>\"?/\\\\|:*]"));
    if(entity.name().indexOf(exp) < 0 && entity.name() != CMPSTR("") && entity.path() != CMPSTR(""))
        return true;
    return false;
}

bool CellProjectEntity::judgeDSFromFile(const QString &path)
{
    QFile loadProject(path);
    if (!loadProject.open(QIODevice::ReadOnly))
        qWarning("Couldn't open save file.");
    QByteArray saveData = loadProject.readAll();
    loadProject.close();
    QJsonDocument loadDoc(QJsonDocument::fromBinaryData(saveData));
    QJsonObject json = loadDoc.object();

    auto type = getType(json["CellProject"].toObject()["Type"].toString());
    if(CellUiGlobal::hasAttribute(DSProject, type))
        return true;
    return false;
}

void CellProjectEntity::print() const
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
