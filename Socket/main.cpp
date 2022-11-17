#include "include.hpp"
#include <algorithm>
#include <array>

namespace LTK {
    template <typename Array, typename Func>
    void foreach(Array array, const size_t Size, Func func) {
        for (size_t i = 0; i < Size; ++i) {
            func(array[i]);
        };
    };

    template <typename Array>
    Array FillArray(const size_t Size) {
        Array array;
        for (size_t i = 0; i < Size; ++i) {
            array[i] = i;
        }
        return array;
    };
    template<typename T, typename Func>
    T TemplateMethod(const T& a, const T& b, Func func) {
        T res = a + b;
        func(res);
        return std::move(res);
    };
    template<typename Func, typename Result, typename IfResultFunc>
    void WhileTemplateFunction(Func func, IfResultFunc ifFunc) {
        Result res;
        bool bLoop = true;
        while(bLoop) {
            res = func(res);
            bLoop = ifFunc(res);
        };
    };
};


int Loop(int a) {
    std::cout << a << std:: endl;
    ++a;
    return a;
};

auto TestTemplateFunction = []() {
    auto ifFunc = [](int& a) { return a < 50; };
    LTK::WhileTemplateFunction<decltype(Loop), int, decltype(ifFunc)>(Loop, ifFunc);
};
int main() {
    return 0;
};