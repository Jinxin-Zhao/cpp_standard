#include <iostream>
#include <mutex>

#include "test_template.h"
#include "unique_ptr.h"
#include "any.h"

template <typename... T>
void f(T... arg){
    std::cout<< sizeof...(arg)<<std::endl;
}

void print(){
    std::cout<< "empty" << std::endl;
}

//void print(int e){
//    std::cout<< "one parameter "<< e << std::endl;
//}




template <typename T,typename ... Args>
void print(T head, Args ...rest){
    std::cout<< "parameter " << head << std::endl;
    print(rest...);
}

class TestConstructor{
public:
    //TestConstructor(std::initializer_list<long double> il);
    TestConstructor(const TestConstructor & tc){}
    TestConstructor(int i, double j){}

    TestConstructor(std::initializer_list<bool> il){}
};
#include <unistd.h>

class test_pkg {
public:
    test_pkg(){
        buf = NULL;
    }
    void construct();
    ~test_pkg(){
        delete buf;
    }
    int *buf;
};

void test_pkg::construct()
{
    delete buf;
    buf = new int(19);
}

void handle(){
    test_pkg tp;
    tp.construct();
}

int main()
{
    std::string tem;
    std::to_string(3);

    //TestConstructor tc{1, 5.0};
    f();
    f(1);
    f(1,2);
    //
    print(1,2,3,4);

//    std::once_flag aa;
//    MemoryPool<int>  mem;
//
//    test_pkg temp_t;
//
//    for(auto i =0 ; i < 100; i++){
//        std::thread t(handle);
//    }


    std::cout << "============= test any class =================" << std::endl;
    std::list<any> any_list;
    any_list.push_back(10);
    any_list.push_back(std::string("hello"));
    any anyone;
    for (auto it = any_list.begin(); it != any_list.end(); ++it){
        anyone = *it;
        if (anyone.type() == typeid(int)){
            std::cout << any_cast<int>(*it) << std::endl;
        } else if (anyone.type() == typeid(std::string)) {
            std::cout << any_cast<std::string>(*it).c_str() << std::endl;
        }
    }


    return 0;
}
