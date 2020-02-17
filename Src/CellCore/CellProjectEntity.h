// This Module Declares Entity Class For Document Of Cell.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This File May Be Used Under The Terms Of The GNU General Public License
// version 3.0 As Published By The Free Software Foundation And Appearing In
// The File LICENSE Included In The Packaging Of This File.
#ifndef CELLPROJECT_H
#define CELLPROJECT_H

#include <QMetaType>

class QJsonObject;

class CellProjectEntity{
public:
    enum CellProjectEntityType{
        _CELLDEEPLEARNING = 0, _PREDICTEARTHQUAKE,
        _CPP             , _PYTHON,
        _EMPTY
    };
    enum CellProjectEntityIndex{
        _NAME = 0, _MODIFIEDTIME,
        _SIZE,     _TYPE,
        _PATH
    };

    explicit CellProjectEntity();
    ~CellProjectEntity() = default;

    static const QString         getType(CellProjectEntityType type);
    static CellProjectEntityType getType(const QString &type);

    inline
    void setName(const QString &name) { this->mName = name; }

    inline
    void setPath(const QString &path) { this->mPath = path; }

    inline
    void setType(const CellProjectEntityType &type) { this->mType = type; }

    inline
    void setsize(const int &size) { this->mSize = size; }

    inline
    void setModifiedTime(const QString &time) { this->mModifiedTime = time; }

    inline const QString&
    name() { return mName; }

    inline const QString&
    path() { return mPath; }

    inline const CellProjectEntityType&
    type() { return mType; }

    inline const int&
    size() { return mSize; }

    inline const QString
    code() { return mCode; }

    inline void
    setCode(const QString &code) { mCode = code; }

    inline const QString&
    modifiedTime() { return mModifiedTime; }

    void print();

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
private:
    CellProjectEntityType mType = _CELLDEEPLEARNING;
    QString               mName;
    QString               mModifiedTime;
    QString               mPath;
    QString               mCode;
    int                   mSize;
};

Q_DECLARE_METATYPE(CellProjectEntity);

#endif // CELLPROJECT_H
