#pragma once
#include "include.h"

namespace AdapterPattern
{
    using namespace std;

class ClientClass {
    public:
    virtual void DoSomething() { cout << "Client class is doing something\n"; };
};
class Adaptee {
    string m_str = "Hello, I'm adaptee.";
    friend class Adapter;
    public:
    void DoSomething() { cout << m_str << " Adaptee class is doing something\n"; };
};
class Adapter : public ClientClass {
    Adaptee* m_pAdaptee_a = nullptr;
    public:
    Adapter(Adaptee* adaptee) : m_pAdaptee_a(adaptee) {};
    void DoSomething() override {
        m_pAdaptee_a->m_str = "Hello, I'm adapter for adaptee. I'm trying to fit adaptee to clientclass.";
        m_pAdaptee_a->DoSomething();
    };
};
void ClientCode(ClientClass* cclass) {
    cclass->DoSomething();

};
void Run() {
    std::cout << "Adapter pattern:\n";
    AdapterPattern::ClientClass cl;
    ClientCode(&cl);
    AdapterPattern::Adaptee adaptee;
    //ClientCode(&adaptee); //error, different interface
    AdapterPattern::Adapter adapter(&adaptee);
    AdapterPattern::ClientCode(&adapter);
};
} // namespace AdapterPattern

