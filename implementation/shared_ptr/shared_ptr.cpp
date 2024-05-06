//
// Created by Xin A on 2021-01-27.
//

#include "shared_ptr.h"

RCObject::RCObject():refCount(0),shareable(true){
}

RCObject::RCObject(const RCObject &rhs):refCount(0),shareable(true){

}
RCObject & RCObject::operator=(const RCObject& rhs){
    return *this;
}

void RCObject::addReference(){
    ++refCount;
}
void RCObject::removeReference(){
    if(--refCount == 0)
        delete this;
}
void RCObject::markUnshareable(){
    shareable = false;
}
bool RCObject::isShareable() const{
    return shareable;
}
bool RCObject::isShared() const{
    return refCount > 1;
}

////
void SString::StringValue::init(const char *initValue)
{

}
