#pragma once
#include "include.h"

//TODO: resolve circular dependency and forward decalration
namespace StatePattern {

    class IState {
        public:
        virtual ~IState() {};
        virtual void Run() = 0;
    };

    class ClientClass {
        IState* m_pCurrentState_a = new State1();
            public:
        void ChangeState(IState* newState) { 
            std::cout << "Client class is changing state\n";
            m_pCurrentState_a = newState;
        };
        void RunState() { m_pCurrentState_a->Run(); };
    };
    class AState {
        protected:
        ClientClass* m_pClientClass_a = nullptr;
        AState(ClientClass* clientClass) : m_pClientClass_a(clientClass) {};
    };
    class State1 : public IState, public AState {
        public:
        State1(ClientClass* clientClass) : AState(clientClass) {};
        virtual void Run() override {
            std::cout << "Running state1\n";
            AState::m_pClientClass_a->ChangeState(new State2());
        };
    };
    class State2 : public IState, public AState  {
        public:
        State2(ClientClass* clientClass) : AState(clientClass) {};
        virtual void Run() override {
            std::cout << "Running state2\n";
            AState::m_pClientClass_a->ChangeState(new State3());
        };

    };
    class State3 : public IState, public AState  {
        public:
        State3(ClientClass* clientClass) : AState(clientClass) {};
        virtual void Run() override {
            std::cout << "Running state3\n";
        };

    };
    

    void ClientCode() {
        ClientClass clClass;
        clClass.RunState();
    };
    void Run() {
        ClientCode();
    };
}