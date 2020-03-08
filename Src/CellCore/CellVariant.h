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
union _Data{
    QColor *color;
};
public:
enum class Type{
    Color
};
    //! The default constructor that deleted is because
    //! you must offer a explicit & implicit conversion.
    CellVariant() = delete;

    CellVariant(CellVariant &other) noexcept;

    CellVariant(Cell::CellGrayColor value) noexcept;

    CellVariant(Cell::CellThemeColor) noexcept;

    CellVariant(const QColor &color) noexcept;

    CellVariant& operator=(CellVariant &other) noexcept;

    CellVariant& operator=(Cell::CellGrayColor value) noexcept;

    CellVariant& operator=(Cell::CellThemeColor value) noexcept;

    ~CellVariant() noexcept;

    inline QColor
    toColor() const { return *mData.get()->color; }

private:
    std::unique_ptr<_Data> mData;
    Type mType;
};

#endif // CELLVARIANT_H
