#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 

#define PRIVATESUBS 
#include "MyPtr.hpp"
#include "MySwap.hpp"
#include "MyForward.hpp"
#include "TestClass.hpp"

auto testSharedPtrs_l = []() {
        int data = 100;
        int data2 = 200;
        char data3 = 'a';
        std::shared_ptr<int> spInt(&data);
        std::unique_ptr<int> asdsad(&data);
        std::shared_ptr<int> spInt2(&data2);
        std::shared_ptr<char> spInt3(&data3);
        auto checkShared = [&]() { std::cout << *spInt << std::endl <<  *spInt2 << std::endl; }; //TODO: create cpp note about using lambdas
        //spInt = spInt2; //copy
        //spInt = std::move(spInt2); ///move, second will be empty
        //spInt = spInt3; //error
        //spInt.swap(spInt2); //just swap
    };
    
auto testMyPtr_l = []() {
    LTK::Unique<int> MyPtr(new int(10));
    std::cout << MyPtr.Get();
};
auto testUnique_l = []() {
    LTK::Unique<int> Ptr = LTK::NewUnique<int>(10);
    std::cout << Ptr.Get() << std::endl;
    auto Ptr2 = std::move(Ptr);
    std::cout << Ptr2.Get() << std::endl;
    std::cout << Ptr.Get() << std::endl; //exception, that's correct
};
auto testShared_l = []() {
    auto Ptr = LTK::NewShared<int>(10);
    std::cout << Ptr.Get() << std::endl;
    std::cout << LTK::Shared<int>::count << std::endl;
    auto Ptr2 = Ptr;
    std::cout << LTK::Shared<int>::count << std::endl;
    auto Ptr3(Ptr2);
    std::cout << LTK::Shared<int>::count << std::endl;

    auto Ptr4 = LTK::NewShared<TestClass<int, std::string>>(20, "Hello");
    std::cout << Ptr4.Get().pub << " " << Ptr4.Get().priv << std::endl;
    
    int* shared = new int(200);
    {
        auto Ptr5 = LTK::Shared<int>(shared);
    }
    std::cout << *shared;

};


void TestMoveAndSwap() {
    TestClass<int, char> cls1(10, 'a');
    TestClass<int, char> cls2(20, 'f');
    auto Print_l = [&]() {
        std::cout << cls1.pub << cls1.priv << cls2.pub << cls2.priv;
    };
    auto MySwapTest_l = [&]() {
        LTK::Swap(cls1, cls2);
        Print_l();
    };
    auto TestMove_l = [&]() {
        cls1 = std::move(cls2);
        Print_l();
    };  
    //TestMove_l();

    std::swap(cls1, cls2);
    Print_l();
};



class Factory {
    public:
    struct TestClass {
        int data = 200;
    };
    LTK::Unique<TestClass> GetObject() {
        return LTK::NewUnique<TestClass>();
    };
};

class TakesOwnership {
    private:
    LTK::Unique<Factory::TestClass> obj;
    public:
    void Take(LTK::Unique<Factory::TestClass> obj) {
        //this->obj = obj;
    };
};
//to properly use std:move you have not to specify "&&" for moving. This works as assignment moving
void Function(LTK::Unique<Factory::TestClass> obj) { 
    std::cout << obj.Get().data;
};

auto TestFactory_l = []() {
    auto ptr = Factory().GetObject();
    //TakesOwnership to;
    //to.Take(ptr);
    //Function(std::move(ptr));
    std::cout << ptr.Get().data; //exception, that's correct
};


//Owner return ref to it's resource, but the caller cannot free it.
class Owner {
    private:
    LTK::Unique<int> ptr = LTK::NewUnique<int>(254);
    public:
    LTK::Unique<int>& Get() {
        return ptr;
    }; //Return a reference for ensuring that caller will not delete ther resourse
};

auto TestReturningPtr  = []() {
    Owner owner;
    {
        LTK::Unique<int>& obj = owner.Get();
        std::cout << *obj.obj;
    }
    std::cout << *owner.Get().obj;
};


int main() {
    //TestFactory_l();

    return 0;
}