#pragma once
#include "include.h"

namespace ExternTest {
    extern int ExternVar; //defined in main cpp
    extern const int ConstExternVar;
    struct Struct {
        void Do() {
            std::cout << ExternVar << '\n';
            std::cout << ConstExternVar << '\n';
        }
    };
    void Test() {
        Struct s;
        s.Do();
    }
}