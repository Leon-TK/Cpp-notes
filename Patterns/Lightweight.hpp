#pragma once
#include "include.h"

namespace LightweightPattern {
    struct StaticClass {
        int data = 0;
    };
    class ClientClass {
        static StaticClass sclass;
            public:
        void LoadData() { std::cout << "ClientClass data: " << sclass.data << '\n'; };
        void ChangeData() { 
            std::cout << "Changing data\n";
            ++sclass.data;
        };
    };
    void ClientCode() {
        ClientClass c1;
        ClientClass c2;
        c1.LoadData();
        c2.LoadData();
        c1.ChangeData();
        c1.LoadData();
        c2.LoadData();
    };
    void Run() {
        ClientCode();
    };
}