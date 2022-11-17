#pragma once
#include "include.h"

//TODO: create macro for testing this file by pasting main function

namespace TemplateMethodPattern {

    using namespace std;

    class AbstractClass {
        void DoSomething1() { cout << "Abstract class do1\n"; };
        void DoSomething2() { cout << "Abstract class do2\n"; };
        virtual void DoSomething3() { cout << "Abstract class do3\n"; }; //This method can be changed by derived class
        void DoSomething4() { cout << "Abstract class do4\n"; };
        public:
        void publicMethod() { //Public method that is composed from private methods
            DoSomething1();
            DoSomething2();
            DoSomething3();
            DoSomething4();
        };
    };
    class ConcreteClass : public AbstractClass {
        void DoSomething3() override { cout << "Concrete class do3\n"; }; //Changing method behavior
    };

    void ClientCode() {
        ConcreteClass cc;
        cc.publicMethod();  
    }
    void Run() {
        std::cout << "Template method pattern:\n";
        ClientCode();
    };
}