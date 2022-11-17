#pragma once
#include "Mediator.h"
#include "include.h"

//Facade's subsystems can know about each other, but in mediator pattern, subsystems can communicate only through mediator
namespace MediatorPattern {

    void Mediator::Class1Responce() {
        std::cout << "Class1 communicates to mediator\n";
        m_cl2.MediatorCall();
    };
    void Mediator::Class2Responce() {
        std::cout << "Class2 communicates to mediator\n";
        m_cl1.MediatorCall();
    };
    void Mediator::Run() { m_cl1.Do(); };

    void ClientCode() {
        Mediator mediator;
        mediator.Run();
    };
    void Run() { ClientCode(); };
}