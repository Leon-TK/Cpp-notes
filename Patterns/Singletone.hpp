#pragma once
#include "include.h"

namespace SingletonePattern
{
    Class* Singletone::cls = nullptr;
    class Class {};
    class Singletone {
        Singletone();
        static Class* cls;
            public:
        static Class* get() {
            if (cls) { return cls;}
            else { cls = new Class(); }
        };
    };
} // namespace SingletonePattern