// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLVARIANT_H
#define CELLVARIANT_H

#include "CellNamespace.h"
#include "holder.h"

#include <memory>

template <typename Type>
class CellVariant{
public:
    CellVariant();
    CellVariant(const Type&);
    CellVariant(const CellVariant&)
    ~CellVariant();

public:
    CellVariant& swap(CellVariant &rhs);
    CellVariant& operator=(const CellVariant &rhs);
    inline
    bool empty() const noexcept{
        return !content;
    }
    inline
    const std::type_info& type() const{
        return content ? content->type() : typeid(void);
    }
    inline static
    const Type*  CellVariant_Cast(const CellVariant *ptr){
        return CellVariant_Cast(const_cast<CellVariant*>(ptr));
    }
    static Type* CellVariant_Cast(CellVariant *ptr);
    static Type  CellVariant_Cast(CellVariant &rhs);

private:
    placeholder *content;
}














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
