#pragma once

namespace LTK
{
    template<typename T>
    T&& Forward(T& obj) {
        return obj;
    };
} // namespace LTK
