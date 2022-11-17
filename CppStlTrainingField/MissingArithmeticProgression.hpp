#pragma once
#include "include.h"

namespace MissingArihmeticProgression {
    using vec = std::vector<long>;
    static long findMissing(std::vector<long> list){
        const auto size = list.size();
        if (size < 2) { return -1; }
        auto findDiff_l = [&]() -> long {
            //as kata instruction says there can't be situation where first and last diff would be wrong and same
            const auto diff1 = list[1] - list[0];
            const auto diff2 = list[list.size() - 1] - list[list.size() - 2];
            if (diff1 == diff2) { return diff1; }
            else {
                if (diff1 > 0 && diff2 > 0) { //safety check if its not ariphmetic prog
                    return diff1 > diff2 ? diff2 : diff1;
                }
                if (diff1 < 0 && diff2 < 0) {
                    return diff1 > diff2 ? diff1 : diff2;
                }
                return -1;
            }
        };
        const auto diff = findDiff_l();
        for (auto i = 0ull; i < size; ++i) {
            if (i == size - 1) { return -1; } //otherwise next instruction will fail
            if (list[i + 1] - list[i] == diff) { continue; }
            else { return list[i] + diff; }
        }
        return 0;
    }

    void Test() {
        std::cout << findMissing({0,38,114}) << '\n';
    };
}