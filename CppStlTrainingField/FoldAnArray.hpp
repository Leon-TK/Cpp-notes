#pragma once
#include "include.h"

namespace FoldAnArray 
{

    using vec = std::vector<int>;
    class Kata
    {
    public:
        std::vector<int> foldArray(std::vector<int> array, int runs)
        {
            vec result = array;
            
            //frwd decl for lambdas
            auto arrSize = 0ull;
            bool bOdd = false;

            auto reverseArray_l = [](vec& arr) { std::reverse(arr.begin(), arr.end()); };
            auto extractArrays_l = [&](const vec& arr) -> std::pair<vec, vec>{
                size_t halfSize = arrSize / 2; //will be floored if bOdd
                std::pair<vec, vec> pair = {vec(halfSize), vec(halfSize)};
                if (!bOdd) {
                    for (auto i = 0ull; i < arrSize; ++i) {
                        (i < halfSize) ? pair.first[i] = arr[i] : pair.second[i - halfSize] = arr[i];
                    }
                }
                else {
                    for (auto i = 0ull; i < arrSize; ++i) {
                        if (i < halfSize) {
                            pair.first[i] = arr[i];
                        }
                        else {
                            if (i == halfSize) ++i; //jump above the middle
                            pair.second[i - halfSize - 1] = arr[i]; // -1 correction
                        }
                    }
                    
                }
                return pair;
            };
            auto sumArrays_l = [](const vec& arr1, const vec& arr2) -> vec {
                if (arr1.size() != arr2.size()) { throw std::exception(); }
                vec temp(arr1.size());
                for (auto i = 0llu; i < arr1.size(); ++i) {
                    temp[i] = arr1[i] + arr2[i];
                }
                return temp;
            };

            while (runs > 0) {
                arrSize = result.size();
                if (arrSize == 1) { return result; }
                bOdd = arrSize % 2;
                
                int middleElement = -1;
                if (bOdd) { middleElement = result[arrSize / 2]; } //save before result is modified

                auto pair = extractArrays_l(result);
                reverseArray_l(pair.second);
                result = sumArrays_l(pair.first, pair.second);

                if (bOdd) { result.emplace_back(middleElement); }

                --runs;
            }   
            
            return result;
        }
    };

    void Test() {
        Kata kata;
        std::vector<int> actual = kata.foldArray({ 1, 2, 3, 4, 5,2,2,3,4,5,3,4,4,6,3,34,4,5,34,43,5,2,23,5,6 }, 10); //{ 15}
        for (const auto& el : actual) { std::cout << el << '\n'; }
    };
} // namespace FoldAnArray 
