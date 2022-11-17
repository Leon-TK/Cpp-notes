#pragma once
//#include "include.h"
#include "MediatorClasses.h"

//Facade's subsystems can know about each other, but in mediator pattern, subsystems can communicate only through mediator
namespace MediatorPattern {
    
    class Mediator {
        private:
        Class1 m_cl1 = Class1(this);
        Class2 m_cl2 = Class2(this);
        void Class1Responce();
        void Class2Responce();    
        friend class Class1;
        friend class Class2;
        public:
        void Run();
    };
    
    void ClientCode();
    void Run();

}