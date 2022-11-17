#pragma once
#include "include.h"

namespace PrototypePattern
{
    class IPrototype {
            public:
        virtual IPrototype* clone() = 0;
    };
    class Class1 : public IPrototype {
            public:
        Class1(Class1& cls) {};
        virtual IPrototype* clone() override {
            return new Class1(*this);
        };
    };
    class Class2 : public IPrototype {
            public:
        Class2(Class2& cls) {};
        virtual IPrototype* clone() override {
            return new Class2(*this);
        };
    };
    void ClientCode() {

    };
    void Run() {
        ClientCode();
    };
} // namespace PrototypePattern
