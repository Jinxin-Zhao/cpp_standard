#ifndef _C_TEMPLATE_H_
#define _C_TEMPLATE_H_

template <typename... Elements>
class TypeList{};

template <typename List>
class FrontT;

template <typename Head, typename... Tail>
class FrontT<TypeList<Head,Tail...>>{
public:
    using Type = Head;
};

//get the first type of typelist
template <typename List>
using Front = typename FrontT<List>::Type;


#endif