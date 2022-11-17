#pragma once
#include "MediatorClasses.h"
#include "Mediator.h"
#include "include.h"

namespace MediatorPattern {    

    void Class1::Do() {
                std::cout << "Class1 do something\n";
                m_pMediator_a->Class1Responce();
    };
    void Class1::MediatorCall() {
                std::cout << "Mediator call in Class1\n";
    };
    void Class2::Do() {
                std::cout << "Class2 do something\n";
            m_pMediator_a->Class2Responce();
    };
    void Class2::MediatorCall() {
                std::cout << "Mediator call in Class2\n";
    };
}