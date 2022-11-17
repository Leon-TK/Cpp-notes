#pragma once
#include "include.h"

namespace DecoratorPattern {
    class Class {
        public:
        virtual ~Class() {};
        virtual void DoSomething() = 0;
    };
    class AClass {
        protected:
        Class* m_pClass_c = nullptr;
        AClass(Class* cclass) : m_pClass_c(cclass) {};
        virtual ~AClass() { delete m_pClass_c; };
    };
    class ConcreteClass : public Class {
        public:
        ConcreteClass() {};
        void DoSomething() override {
            std::cout << "ConcreteClass doing something\n";
        };

    };
    class DecoratorClass1 : public Class, public AClass  {
        public:
        DecoratorClass1(Class* cclass) : AClass(cclass) {};
        void DoSomething() override {
            std::cout << "DecoratorClass1 doing something\n";
            m_pClass_c->DoSomething();
        };
    };
    class DecoratorClass2 : public Class, public AClass  {
        public:
        DecoratorClass2(Class* cclass) : AClass(cclass) {};
        void DoSomething() override {
            std::cout << "DecoratorClass2 doing something\n";
            m_pClass_c->DoSomething();
        };
    };

    void ClientCode() {
        Class* dclass = new ConcreteClass(); //This class will be called last
        dclass = new DecoratorClass1(dclass);
        dclass = new DecoratorClass2(dclass); //This decorator will be called first
        dclass->DoSomething();
    };

    void Run() {
        std::cout << "Decorator pattern:\n";
        ClientCode();
    };
}