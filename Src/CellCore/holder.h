#ifndef HOLDER_H
#define HOLDER_H

//! Pure Abstract Interface
//! For class holder.
class placeholder
{
public:
    virtual ~placeholder() = default;
    virtual const std::type_info& type() const = 0;
    virtual placeholder* clone() const = 0;
}
//! Core Class Template For Handling 
//! Resources.
template<typename Type>
class holder : public placeholder{
public:
    //! Constructor Allows Explicit Type Casting.
    holder(const Type &value);

public:
    virtual const std::type_info& type() const;
    virtual placeholder* clone() const;

    Type held;

private:
    holder& operator=(const holder&);
}

#endif // HOLDER_H