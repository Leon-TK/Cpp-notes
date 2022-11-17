#pragma once
#include "include.h"

namespace BuilderPattern
{
    class IBuilder {
        public:
        virtual ~IBuilder() {};
        virtual void Step1() = 0;
        virtual void Step2() = 0;
        virtual void Step3() = 0;
    };
    class Builder1 : public IBuilder {
            public:
        class Product1 {};
            private:    
        Product1* m_pProduct_o = nullptr; //_o means "out"
            public:
        Product1* GetProduct() { return m_pProduct_o; };
        void Step1() override {};
        void Step2() override {};
        void Step3() override {};
    };
    class Builder2 : public IBuilder {
            public:
        class Product2 {};
            private:
        Product2* m_pProduct_o = nullptr;
            public:
        Product2* GetProduct() { return m_pProduct_o; };
        void Step1() override {};
        void Step2() override {};
        void Step3() override {};
    };
    class Director {
        IBuilder* m_pBldr_a = nullptr;
        public:
        void Build() {
            m_pBldr_a->Step1();
            m_pBldr_a->Step2();
            m_pBldr_a->Step3();
        };
        void SetBuilder(IBuilder* builder) { m_pBldr_a = builder; };
    };

    void ClientCode() {
        Builder1* builder1 = new Builder1();
        Builder2* builder2 = new Builder2();
        Director director;
        director.SetBuilder(builder1);
        director.Build();
        Builder1::Product1* product1 = builder1->GetProduct();
        director.SetBuilder(builder2);
        director.Build();
        Builder2::Product2* product2 = builder2->GetProduct();
    };
    void Run() {
        ClientCode();
    };
} // namespace BuilderPattern
