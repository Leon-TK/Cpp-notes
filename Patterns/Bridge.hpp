#pragma once
#include "include.h"

namespace BridgePattern {
    using namespace std;

    class Implementation {
        public:
        virtual void DoA() = 0;
        virtual void DoB() = 0;
        virtual void DoC() = 0;
    };
    class Abstraction {
        Implementation* m_pImpl_c = nullptr;
        public:
        Abstraction(Implementation* impl) : m_pImpl_c(impl) {};
        ~Abstraction() { delete m_pImpl_c; };
        void DoA(){
            m_pImpl_c->DoA();
            m_pImpl_c->DoB();
        };

    };
    
    class ConcreteImplementation : public Implementation{
        public:
        virtual void DoA() override {};
        virtual void DoB() override {};
        virtual void DoC() override {};
    };

    class ISocket { //Implementation
        public:
        virtual void SendData(string Data) = 0;
        virtual string GetData() = 0;
        virtual void Bind(int Ip) = 0;
        virtual void Shutdown() = 0;
    };
    class LibSocketWrapper : public ISocket {
        string m_data = "";
        //Lib lib;
        public:
        virtual void SendData(string Data) override {
            cout << "lib socket is sending data\n";
            m_data = "responce from lib socket";
        };
        virtual string GetData() override { return m_data; };
        virtual void Bind(int Ip) override {};
        virtual void Shutdown() override {};
    };
    class OtherLibSocketWrapper : public ISocket {
        string m_data = "";
        //Otherlib lib;
        public:
        virtual void SendData(string Data) override {
            cout << "Other lib socket is sending data\n";
            m_data = "responce from Other lib socket";
        };
        virtual string GetData() override { return m_data; };
        virtual void Bind(int Ip) override {};
        virtual void Shutdown() override {};
    };

    class Program { //Abstraction
        ISocket* m_pSocket_c = new LibSocketWrapper();
        public:
        Program() {};
        ~Program() { delete m_pSocket_c; };
        void ChangeAbstraction(ISocket* socket) { delete this->m_pSocket_c; this->m_pSocket_c = socket;};
        string Send(string Data) {
            m_pSocket_c->SendData(Data);
            return m_pSocket_c->GetData();
        }
    };
    void ClientCode() {
        Program prg;
        string responce = prg.Send("CLient code is sending data1");
        cout << "Program responce: " << responce << '\n';
        prg.ChangeAbstraction(new OtherLibSocketWrapper());
        responce = prg.Send("CLient code is sending data2");
        cout << "Program responce: " << responce << '\n';
    };
    void Run() {
        cout << "Bridge pattern:\n";
        ClientCode();
    };
}
