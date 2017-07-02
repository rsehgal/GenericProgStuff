#include <iostream>


class Test{

public:
    template<typename... Ts>
    void Func(Ts... args){
        std::cout<<"Entered Variadic template function......" << std::endl;
        int size = sizeof...(args);
        std::cout<<"Num of template parameters : " << size << std::endl;
    }
};


int main(){

    Test t;
    t.Func<int,float>(5, 6.50);

    return 0;
}