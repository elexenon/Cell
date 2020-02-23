// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLVARIANT_H
#define CELLVARIANT_H

#include "CellNamespace.h"

#include <memory>

class CellVariant{
union Data{
    QColor *color;
};
public:
enum Type{
    Color
};
    explicit
    CellVariant() = delete;
    CellVariant(CellVariant &other);
    CellVariant(Cell::CellGrayColor value);
    CellVariant(Cell::CellThemeColor);
    CellVariant& operator=(CellVariant &other);
    CellVariant& operator=(Cell::CellGrayColor value);
    CellVariant& operator=(Cell::CellThemeColor value);
    ~CellVariant();
    inline
    QColor toColor() const { return *mData.get()->color; }

private:
    std::unique_ptr<Data> mData;
    Type mType;
};

#endif // CELLVARIANT_H
