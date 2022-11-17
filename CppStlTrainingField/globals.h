#pragma once
#include "include.h"
#include "defines.h"

#pragma region constexprDefine

#if WIN32 == 1
    constexpr bool define_Win32 = true;
#else
    constexpr bool define_Win32 = false;
#endif
#if UNIX == 1
    constexpr bool define_Unix = true;
#else
    constexpr bool define_Unix = false;
#endif
static_assert(define_Unix != define_Win32);

#ifdef NDEBUG
    constexpr bool define_NDebug = true;
#else
    constexpr bool define_NDebug = false;
#endif

constexpr auto GetWelcome() {
    if constexpr (define_Win32) {
        return "Running on Win32";
    }
    if constexpr (define_Unix) {
        return "Running on Unix";
    }
};

//N. Too much assembly code\
use "if constexpr" condition statement in the main function
//const std::string gWelcomeStr = define_Win32 ? "Running on Win32" : \
                                define_Unix ? "Running on Unix" : "";

constexpr auto gWelcomeStr = GetWelcome();


#pragma endregion