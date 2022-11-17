#pragma once

namespace MediatorPattern {

    class Mediator;
    
    class Class1 {
        MediatorPattern::Mediator* m_pMediator_a = nullptr;
            public:
        Class1(MediatorPattern::Mediator* mediator) : m_pMediator_a(mediator) {};
        void Do();
        void MediatorCall();
    };
    class Class2 {
        MediatorPattern::Mediator* m_pMediator_a = nullptr;
            public:
        Class2(MediatorPattern::Mediator* mediator) : m_pMediator_a(mediator) {};
        void Do();
        void MediatorCall();
    };
}