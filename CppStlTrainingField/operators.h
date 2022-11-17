#pragma once

namespace LTK
{
    class OperatorTestClass {
        public:
        int data = 0;
        void operator+() {

        }
    };
    class OperatorTestClass2 {
        public:
        int data = 0;
        OperatorTestClass2 operator+(const OperatorTestClass& other) { // (this + other) = return, other + this won't work because you need to define this in class of "other"
            OperatorTestClass2 neww;
            neww.data = data + other.data;
            return neww;
        }
        OperatorTestClass2 operator+(const OperatorTestClass2& other) { // (this + other) = return
            OperatorTestClass2 neww;
            neww.data = data + other.data;
            return neww; //test if return copies variable by counting on copy
        }
    };

    
} // namespace LTK

//global operator. Testing what overload (class or global) will be invoked
//Testing result: this overload is invoded. class's overload only if here "const" is specified
LTK::OperatorTestClass2 operator+(LTK::OperatorTestClass2& left, LTK::OperatorTestClass2& right) { // (left + right) = return
    LTK::OperatorTestClass2 neww;
    neww.data = left.data + right.data;
    return neww; //test if return copies variable by counting on copy
}

//void operator sos() { std::cout << "SOS\n"; };