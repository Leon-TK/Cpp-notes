#include "include.h"
#include <thread>

auto SomeFunc_l = [](std::string str) {
    std::cout << str << std::endl;
};


void Test() {};
int main() {
    std::thread(Test);
};