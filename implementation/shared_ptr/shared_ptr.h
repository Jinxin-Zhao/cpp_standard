//
// Created by Xin A on 2021-01-27.
//

#ifndef SHARED_PTR_SHARED_PTR_H
#define SHARED_PTR_SHARED_PTR_H

#include <form.h>

template<typename T>
class RCPtr {
public:
    RCPtr(T *realPtr = 0);

    RCPtr(const RCPtr &rhs);

    ~RCPtr();

    RCPtr &operator=(const RCPtr &rhs);

    T *operator->() const;

    T &operator*() const;

private:
    T *pointee;

    void init();
};

template <typename T>
void RCPtr<T>::init()
{
    if(pointee == 0) return;
    if(pointee->isShareable() == false){
        pointee = new T(*pointee);
    }
    pointee->addReference();
}

template <typename T>
RCPtr<T>::RCPtr(T *realPtr):pointee(realPtr)
{
    init();
}
template <typename T>
RCPtr<T>::RCPtr(const RCPtr & rhs):pointee(rhs.pointee)
{
    init();
}

template <typename T>
RCPtr<T>::~RCPtr()
{
    if(pointee)
        pointee->removeReference();
}

template <typename T>
RCPtr<T> & RCPtr<T>::operator=(const RCPtr &rhs)
{
    if(pointee != rhs.pointee){
        if(pointee)
            pointee->removeReference();
        pointee = rhs.pointee;
    }
    return *this;
}

template <typename T>
T & RCPtr<T>::operator*() const
{
    return *pointee;
}

template <typename T>
T * RCPtr<T>::operator->() const
{
    return pointee;
}

//baseClass for reference-counted objects
class RCObject{
public:
    void addReference();
    void removeReference();
    void markUnshareable();
    bool isShareable() const;
    bool isShared() const;

protected:
    RCObject();
    RCObject(const RCObject &rhs);
    RCObject &operator=(const RCObject& rhs);
    virtual  ~RCObject() = 0;

private:
    int refCount;
    bool shareable;
};

class SString{
public:
    SString(const char * value = "");
    const char &operator[](int index) const;
    char &operator[](int index);

private:
    struct StringValue : public RCObject{
        char * data;
        StringValue(const char * initValue);
        StringValue(const StringValue & rhs);
        void init(const char * initValue);
        ~StringValue();
    };
    RCPtr<StringValue> value;
};


class shared_ptr {

};


#endif //SHARED_PTR_SHARED_PTR_H
