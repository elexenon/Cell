#include "CellVariant.h"
#include "Kits/CellGlobalMacros.h"

CellVariant::CellVariant(CellVariant &other):
    mType(other.mType)
{
    mData = std::move(other.mData);
}

CellVariant::CellVariant(Cell::CellGrayColor value)
{
    mType = Color;
    mData.reset(new Data);
    mData.get()->color = new QColor(value, value, value);
}

CellVariant::CellVariant(Cell::CellThemeColor type)
{
    mType = Color;
    mData.reset(new Data);
    mData.get()->color = new QColor;
    switch(type){
        case Cell::pureGreen:
        mData.get()->color->setRgb(0, 255, 0);
        break;
        case Cell::NavyBlue:
        mData.get()->color->setRgb(79, 147, 184);
        break;
        case Cell::ExitRed:
        mData.get()->color->setRgb(220, 20, 60);
        break;
    }
}

CellVariant &CellVariant::operator=(CellVariant &other)
{
    if(this == &other)
        return *this;
    mType = other.mType;
    mData = std::move(other.mData);
    return *this;
}

CellVariant &CellVariant::operator=(Cell::CellGrayColor value)
{
    CellVariant tmp(value);
    return operator=(tmp);
}

CellVariant &CellVariant::operator=(Cell::CellThemeColor value)
{
    CellVariant tmp(value);
    return operator=(tmp);
}

CellVariant::~CellVariant()
{
    if(mType == Color && mData) delete mData.get()->color;
}
