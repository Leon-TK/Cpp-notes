#pragma once
#include "include.h"

namespace ProxyPattern {

    class ClientClass {
            public:
        virtual ~ClientClass() {};
        virtual void Do1() = 0;
        virtual void Do2() = 0;
        virtual void Do3() = 0;
    };
    class Implementation : public ClientClass {
            public:
        Implementation() {};
        virtual void Do1() override { std::cout << "Implementation Do1\n"; };
        virtual void Do2() override { std::cout << "Implementation Do2\n"; };
        virtual void Do3() override { std::cout << "Implementation Do3\n"; };
    };
    class ProxyImplementation : public ClientClass {
        Implementation* m_pImpl_c = nullptr;
            public:
        ProxyImplementation(Implementation* impl) : m_pImpl_c(impl) {};
        ~ProxyImplementation() { delete m_pImpl_c; };
        virtual void Do1() override { std::cout << "ProxyImplementation Do1\n"; m_pImpl_c->Do1(); };
        virtual void Do2() override { std::cout << "ProxyImplementation Do2\n"; };
        virtual void Do3() override { std::cout << "ProxyImplementation Do3\n"; };
    };
    void ClientCode() {
        ClientClass* cc = new Implementation();
        ClientClass* cc2 = new ProxyImplementation(new Implementation());
        cc->Do1();
        cc2->Do1();
        cc->Do2();
        cc2->Do2();
    };
    void Run() {
        ClientCode();
    };
}