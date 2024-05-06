#ifndef  _CEL_UNIQUE_PTR_H_
#define  _CEL_UNIQUE_PTR_H_

#include <memory>
#include <type_traits>
#include "template.h"

class Investment{
public:
    Investment(){}
};

class Stock : public Investment{
public:
    using Investment::Investment;
};

class Bond : public Investment{
    using Investment::Investment;
};

class RealEstate : public Investment{
    using Investment::Investment;
};

//using inv_typeList = TypeList<Stock, Bond, RealEstate>;

auto delInvmt = [](Investment * pIns){
    std::cout << "delete Investment" << std::endl;
    delete pIns;
};

template<typename... Ts>
std::unique_ptr<Investment, decltype(delInvmt)> makeInvestment(Ts&&... params){
    std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);
    if (std::is_same<Front<TypeList<Ts...>>,Stock>::value){
        std::cout << "enter into stock \n";
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    if (std::is_same<Front<TypeList<Ts...>>,Bond>::value){
        std::cout << "enter into Bond \n";
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    if (std::is_same<Front<TypeList<Ts...>>,RealEstate>::value){
        std::cout << "enter into RealEstate \n";
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }
    return pInv;
}






#endif