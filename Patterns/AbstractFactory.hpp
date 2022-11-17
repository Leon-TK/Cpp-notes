#pragma once
#include "include.h"

namespace AbstractFactory {

    class IProduct1 {};
    class IProduct2 {};
    class F1Product1 : public IProduct1 {};
    class F1Product2 : public IProduct2 {};
    
    class F2Product1 : public IProduct1 {};
    class F2Product2 : public IProduct2 {};

    class IAbstractFactory {
            public:
        virtual ~IAbstractFactory() {};
        virtual IProduct1* GetProduct1() = 0;
        virtual IProduct2* GetProduct2() = 0;
    };
    class AbstractFactory1 : public IAbstractFactory {
            public:
        virtual IProduct1* GetProduct1() override { return new F1Product1(); };
        virtual IProduct2* GetProduct2() override { return new F1Product2(); };
    };
    class AbstractFactory2 : public IAbstractFactory {
            public:
        virtual IProduct1* GetProduct1() override { return new F2Product1(); };
        virtual IProduct2* GetProduct2() override { return new F2Product2(); };
    };
    void ClientCode() {
        IAbstractFactory* factory1 = new AbstractFactory1();
        IAbstractFactory* factory2 = new AbstractFactory2();
        IProduct1* f1product1 = factory1->GetProduct1();
        IProduct2* f1product2 = factory1->GetProduct2();
        IProduct1* f2product1 = factory2->GetProduct1();
        IProduct2* f2product2 = factory2->GetProduct2();
    };
    void Run() {
        ClientCode();
    };
}