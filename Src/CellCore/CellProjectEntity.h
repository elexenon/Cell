// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
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
