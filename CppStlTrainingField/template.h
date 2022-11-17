#pragma once

namespace LTK {
    template<typename T>
    T func(T t);

    //extern template int func<int>(int t);
    template<auto Val> // auto used only for non type template param
    constexpr auto val = Val;

    template <auto Val> // <template T, T v> without auto
    struct integra {
        static constexpr auto val = Val;
        using value_type = decltype(Val); // = T without auto
        using type = integra<Val>; //identity type. type of exacly instatiated template
        constexpr operator value_type() { return val; }
        constexpr value_type operator()() { return val; }
    };
    
}

