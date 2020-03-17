// This Module Declares Entity Class For Document Of Cell.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLPROJECT_H
#define CELLPROJECT_H

#include <QMetaType>

class QJsonObject;

class CellProjectEntity{
public:
    enum ProjectType{
        CellDeepLearning  = 0x001,
        Empty             = 0x002,
        CPP               = 0x004,
        Python            = 0x008,
        ImageClassify     = 0x010,
        ObjectDetect      = 0x020,
        PredictEarthquake = 0x040,
        WSProject         = CellDeepLearning | Empty | CPP | Python,
        DSProject         = ImageClassify | ObjectDetect | PredictEarthquake
    };
    //! Register Enum Type "ProjectType"
    //! Into QFlags.
    Q_DECLARE_FLAGS(EntityType, ProjectType)
    enum CellProjectEntityIndex{
        Name = 0, ModifiedTime,
        Type,     Path
    };

    explicit CellProjectEntity() noexcept;

    CellProjectEntity(const QString&, const QString&,
                      ProjectType, const QString&) noexcept;

    static const QString
    getType(ProjectType type);

    static ProjectType
    getType(const QString &type);

    static CellProjectEntity
    convert(const QList<QStandardItem*> &items);

    static bool
    validEntity(CellProjectEntity &entity);

    static bool
    judgeDSFromFile(const QString &path);

    inline void
    setName(const QString &name) { this->mName = name; }

    inline void
    setPath(const QString &path) { this->mPath = path; }

    inline void
    setType(const ProjectType &type) { this->mType = type; }

    inline void
    setModifiedTime(const QString &time) { this->mModifiedTime = time; }

    inline const QString&
    name() const { return mName; }

    inline const QString&
    path() const { return mPath; }

    inline const ProjectType&
    type() const { return mType; }

    inline const QString
    code() const { return mCode; }

    inline void
    setCode(const QString &code) { mCode = code; }

    inline const QString&
    modifiedTime() const { return mModifiedTime; }

    void
    print() const;

    void
    read(const QJsonObject &json);

    void
    write(QJsonObject &json);

private:
    mutable QString     mName;
    mutable QString     mModifiedTime;
    mutable ProjectType mType = CellDeepLearning;
    mutable QString     mPath;
    mutable QString     mCode;
};

Q_DECLARE_METATYPE(CellProjectEntity);

#endif // CELLPROJECT_H
