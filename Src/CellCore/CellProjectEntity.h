// This Module Declares Entity Class For Document Of Cell.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This File May Be Used Under The Terms Of The GNU General Public License
// version 3.0 As Published By The Free Software Foundation And Appearing In
// The File LICENSE Included In The Packaging Of This File.
#ifndef CELLPROJECT_H
#define CELLPROJECT_H

class CellProjectEntity{
public:
    enum CellProjectEntityType{
        _CELLDEEPLEARNING, _PREDICTEARTHQUAKE,
        _CPP             , _PYTHON,
        _EMPTY
    };
    explicit CellProjectEntity();
    ~CellProjectEntity() = default;

    inline void setName(const QString &name) { this->name = name; }
    inline void setPath(const QString &path) { this->path = path; }
    inline void setType(const CellProjectEntityType &type) { this->type = type; }
    inline void setsize(const QString &size) { this->size = size; }
    inline void setModifiedTime(const QString &time) { this->modifiedTime = time; }
private:
    CellProjectEntityType type;
    QString               name;
    QString               modifiedTime;
    QString               path;
    QString               size;
};

#endif // CELLPROJECT_H
