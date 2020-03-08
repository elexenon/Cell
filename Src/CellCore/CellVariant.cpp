#include "CellVariant.h"
#include "Kits/CellGlobalMacros.h"

#include <cassert>

CellVariant::CellVariant(CellVariant &other) noexcept
{
    if(mType == Type::Color)
        delete mData.get()->color;
    mType = other.mType;
    mData = std::move(other.mData);
}

CellVariant::CellVariant(Cell::CellGrayColor value) noexcept
    :mType(Type::Color)
{
    mData.reset(new _Data);
    mData.get()->color = new QColor(value, value, value);
}

CellVariant::CellVariant(Cell::CellThemeColor type) noexcept
    :mType(Type::Color)
{
    mData.reset(new _Data);
    mData.get()->color = new QColor;
    switch(type){
    case Cell::CellThemeColor::pureGreen:
        mData.get()->color->setRgb(0, 255, 0);
        break;
    case Cell::CellThemeColor::NavyBlue:
        mData.get()->color->setRgb(79, 147, 184);
        break;
    case Cell::CellThemeColor::ExitRed:
        mData.get()->color->setRgb(220, 20, 60);
        break;
    case Cell::CellThemeColor::yellowGreen:
        mData.get()->color->setRgb(228, 246, 212);
    }
}

CellVariant::CellVariant(const QColor &color) noexcept:
    mType(Type::Color)
{
    mData.reset(new _Data);
    mData.get()->color = new QColor(color);
}

CellVariant &CellVariant::operator=(CellVariant &other) noexcept
{
    if(this == &other)
        return *this;
    if(mType == Type::Color)
        delete mData.get()->color;
    mType = other.mType;
    mData = std::move(other.mData);
    return *this;
}

CellVariant &CellVariant::operator=(Cell::CellGrayColor value) noexcept
{
    CellVariant tmp(value);
    return operator=(tmp);
}

CellVariant &CellVariant::operator=(Cell::CellThemeColor value) noexcept
{
    CellVariant tmp(value);
    return operator=(tmp);
}

CellVariant::~CellVariant() noexcept
{
    if(mType == Type::Color && mData.get()) delete mData.get()->color;
}

