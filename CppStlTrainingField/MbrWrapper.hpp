#pragma once

#include <memory_resource>
#include <chrono>
#include <list>
namespace MrbFactory
{
    template<typename TAllocator, typename TResource, size_t TSize>
    struct MBR
    {
        std::array<std::byte, TSize> m_buffer;
        TResource m_resource;
        TAllocator m_allocator;

        MBR() : m_resource{m_buffer.data(), m_buffer.size()}, m_allocator{&m_resource} {
        };

        const TAllocator& GetAllocator() {
            return m_allocator;
        };
    };
    
    template<typename T, size_t TSize>
    using MonotonicStack = MBR<std::pmr::polymorphic_allocator<T>, std::pmr::monotonic_buffer_resource, TSize>;

    void Test() {
        using vecType = int;
        const size_t nIterations = 1000;
        //const size_t measureNIteration = 10;
        const size_t bufferSize = nIterations * sizeof(vecType) * 2 * measureNIteration;

        auto fillVector_l = [=] (auto& arg) {
            arg.reserve(bufferSize);
            for (auto i = 0ull; i < nIterations; ++i) {
                arg.push_back(i);
            }
        };
        auto readVector_l = [=] (auto& arg) {
            arg.reserve(bufferSize);
            for (auto i = 0ull; i < nIterations; ++i) {
                auto var = arg[i];
            }
        };
        auto writeList_l = [=] (auto& arg) {
            for (auto i = 0ull; i < nIterations; ++i) {
                arg.push_back(i);
            }
        };
        auto measure_l = [](size_t nIteration, auto& func, auto& vector){
                auto start = std::chrono::high_resolution_clock::now();
                func(vector);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
        };

        {
            std::cout << "Standart\n";
            std::list<vecType> list{};
            std::vector<vecType> vector{};
            measure_l(measureNIteration, fillVector_l, vector);
        }
        {
            std::cout << "Monotonic\n";
            MonotonicStack<vecType, bufferSize> mbr;
            std::pmr::list<vecType> list{{}, mbr.GetAllocator()};
            std::pmr::vector<vecType> vector{{}, mbr.GetAllocator()};
            measure_l(measureNIteration, fillVector_l, vector);
        }

    };
} // namespace MrbFactory
