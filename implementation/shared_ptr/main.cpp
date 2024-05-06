#include <iostream>
#include <memory>


class testShPtr : public std::enable_shared_from_this<testShPtr>{

};

int main()
{
    std::shared_ptr<int> obj(new int(1));
    obj.get();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}