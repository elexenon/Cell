#include "holder.h"

template <typename Type>
holder<Type>::holder(const Type &value):held(value)
{}

template <typename Type>
const std::type_info& holder<Type>::type() const{
    return typeid(Type);
}

template <typename Type>
placeholder* holder<Type>::clone() const{
    return new holder(held);
}