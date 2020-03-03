#include "CellVariant.h"
#include "Kits/CellGlobalMacros.h"

template <typename Type>
CellVariant<Type>::CellVariant() noexcept
    :content(nullptr){}

template <typename Type>
CellVariant<Type>::CellVariant(const Type &value) noexcept
    :content(new holder<Type>(value)){}

template <typename Type>
CellVariant<Type>::CellVariant(const CellVariant &other) noexcept
    :content(other.content ? other.content->clone() : nullptr){}

template <typename Type>
CellVariant<Type>::~CellVariant() noexcept
{
    delete content;
}

template <typename Type>
CellVariant& CellVariant<Type>::swap(CellVariant &rhs) noexcept
{
    std::swap(content, rhs.content);
    return *this;
}

template <typename Type>
CellVariant& CellVariant<Type>::operator=(const CellVariant &rhs)
{
    static_cast<CellVariant>(rhs).swap(*this);
    return *this;
}

template <typename Type>
Type* CellVariant<Type>::CellVariant_Cast(CellVariant *ptr){
    return (ptr && ptr->type() == typeid(Type)) ?
            &static_cast<CellVariant::holder<Type>*>(ptr->content)->held:
            nullptr;
}

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

CellVariant::~CellVariant() noexcept
{
    if(mType == Color && mData) delete mData.get()->color;
}
