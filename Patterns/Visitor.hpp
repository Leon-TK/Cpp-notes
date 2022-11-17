#pragma once
#include "include.h"

namespace VisitorPattern
{
    class Class1;
    class Class2;
    class Class3;
    class Visitor {
        public:
        void Visit(Class1* cls) {
            std::cout << "Visitor visits class1\n";
        };
        void Visit(Class2* cls) {
            std::cout << "Visitor visits class2\n";
        };
        void Visit(Class3* cls) {
            std::cout << "Visitor visits class3\n";
        };
    };
    class Visitable {
            public:
        virtual ~Visitable() {};
        virtual void Accept(Visitor* visitor) = 0;
    };
    class Class1 : public Visitable {
            public:
        virtual void Accept(Visitor* visitor) {
            visitor->Visit(this);
        };
    };
    class Class2 : public Visitable {
            public:
        virtual void Accept(Visitor* visitor) {
            visitor->Visit(this);
        };

    };
    class Class3 : public Visitable {
            public:
        virtual void Accept(Visitor* visitor) {
            visitor->Visit(this);
        };
    };

    

    void ClientCode() {
        Visitor visitor;
        Class1 cl1;
        cl1.Accept(&visitor);
        Class2 cl2;
        cl2.Accept(&visitor);
        Class3 cl3;
        cl3.Accept(&visitor);
    };
    void Run() { 
        ClientCode();
    };
} // namespace VisitorPattern
