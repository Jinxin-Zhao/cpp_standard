#ifndef  __ANY_H_
#define  __ANY_H_

#include "common.h"

class any {
public:
    class placeholder {
    public:
        virtual ~placeholder(){}

    public:
        virtual const std::type_info & type() const = 0;
        virtual placeholder * clone() const = 0;
    };

    template<typename ValueType>
    class holder : public placeholder {
    public:
        holder(const ValueType & value) : held(value){}

    public:
        virtual const std::type_info & type() const {
            return typeid(ValueType);
        }
        virtual placeholder * clone() const {
            return new holder(held);
        }

    public:
        ValueType held;
    };

public:
    any() : content(nullptr){}

    template<typename ValueType>
    any(const ValueType & value) : content(new holder<ValueType>(value)){}

    any(const any & other) : content(other.content ? other.content->clone() : nullptr){

    }
    ~any(){
        if (content != nullptr) {
            delete content;
        }
    }

private:
    placeholder * content;
    template<typename ValueType>
    friend ValueType any_cast(const any & operand);

public:
    const std::type_info & type() const {
        return content ? content->type() : typeid(void);
    }

};

template <typename ValueType>
ValueType any_cast(const any & operand) {
    assert(operand.type() == typeid(ValueType));
    return static_cast<any::holder<ValueType> *>(operand.content)->held;
}

#endif