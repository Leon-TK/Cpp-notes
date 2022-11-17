#pragma once
#include "include.h"

namespace ChainPattern {

    struct Task {
        std::string login = "Bob";
        std::string password = "Ross";
        std::string data = "Paint";
    };
    class ChainElement {
        ChainElement* m_pNextElement_c;
        bool bLast = false;

            protected:
        virtual bool ChainLogic(Task task) = 0;

            public:
        ~ChainElement() { delete m_pNextElement_c; };
        ChainElement(ChainElement* nextElement, bool bLast = false) : m_pNextElement_c(nextElement), bLast(bLast) {};
        bool Run(Task task) {
            if (bLast) { return ChainLogic(task); }
            else { return ChainLogic(task) && m_pNextElement_c->Run(task); }
        };
        
    };

    class AuthChain : public ChainElement {
        bool ChainLogic(Task task) override {
            return task.login == "Bob" && task.password == "Ross";
        };

            public:
        AuthChain(ChainElement* nextElement, bool bLast = false) : ChainElement(nextElement, bLast) {}; 
    };

    class LogChain : public ChainElement {
        bool ChainLogic(Task task) override {
            std::cout << "Task is being processed.\n";
            return true;
        };

            public:
        LogChain(ChainElement* nextElement, bool bLast = false) : ChainElement(nextElement, bLast) {};
        
    };

    class CheckChain : public ChainElement {
        bool ChainLogic(Task task) override {
            return task.data == "Paint";
        };

            public:
        CheckChain(ChainElement* nextElement, bool bLast = false) : ChainElement(nextElement, bLast) {};
        
    };

    void ClientCode() {
        Task task = {"Bob", "Ross", "Paint"};
        ChainElement* chain = new AuthChain(new LogChain(new CheckChain(nullptr, true)));
        if (chain->Run(task)) { std::cout << "Complete.\n"; }
        else { std::cout << "Failed.\n"; }
    };
    void Run() {
        ClientCode();
    };
}
