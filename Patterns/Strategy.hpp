#pragma once
#include "include.h"

namespace StrategyPattern {

    using namespace std;

    //Strategy pattern is about HOW TO DO. In other hand the command pattern is about WHAT TO DO.
    class Strategy {
        public:
        virtual ~Strategy() {};
        virtual void Run() = 0;
    };
    class ConcreteStrategy1 : public Strategy {
        public:
        void Run() { cout << "Running strategy 1\n"; };
    };
    class ConcreteStrategy2 : public Strategy {
        public:
        void Run() { cout << "Running strategy 2\n"; };
    };

    class StrategyClientClass {
        Strategy* m_pStrategy_c = nullptr;
        public:
        ~StrategyClientClass() { delete m_pStrategy_c; };
        StrategyClientClass(Strategy* strategy) : m_pStrategy_c(strategy) {};
        void SomeMethod() {
            m_pStrategy_c->Run();
        };
    };

    void ClientCode() {
        StrategyPattern::StrategyClientClass strcc(new StrategyPattern::ConcreteStrategy1());
        strcc.SomeMethod();
        StrategyPattern::StrategyClientClass strcc2(new StrategyPattern::ConcreteStrategy2());
        strcc2.SomeMethod();
    };
    void Run() {
        std::cout << "Strategy pattern:\n";
        ClientCode();
    };
}