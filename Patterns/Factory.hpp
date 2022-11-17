#pragma once
#include "include.h"

namespace FactoryPattern
{
    class IProduct {};
    class Product1 : public IProduct {};
    class Product2 : public IProduct {};
    class IFactory {
        public:
        virtual ~IFactory() {};
        virtual IProduct* GetProduct() = 0;
    };
    class Factory1 : public IFactory {
        public:
        virtual IProduct* GetProduct() override { return new Product1(); };
    };
    class Factory2 : public IFactory {
        public:
        virtual IProduct* GetProduct() override { return new Product2(); };
    };
    void ClientCode() {
        IFactory* factory1 = new Factory1();
        IProduct* product1 = factory1->GetProduct();
        
        IFactory* factory2 = new Factory2();
        IProduct* product1 = factory2->GetProduct();
    };
    void Run() {
        ClientCode();
    };
} // namespace FactoryPattern
