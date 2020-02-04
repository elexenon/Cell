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
        _WORKSHOP
    };
    explicit CellProjectEntity(const QString &name, const CellProjectEntityType &type);
    ~CellProjectEntity() = default;
private:
    CellProjectEntityType type;
    QString name;
    QString creationTime;   
    QString code;
};

#endif // CELLPROJECT_H
