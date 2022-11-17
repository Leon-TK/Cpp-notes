#pragma once

namespace LTK
{
    template<typename T>
    void Swap(T& obj1, T& obj2) {
        T temp = std::move(obj2);
        obj2 = std::move(obj1);
        obj1 = std::move(temp);
    };
} // namespace LTK
