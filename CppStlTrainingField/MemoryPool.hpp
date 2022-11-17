#pragma once
#include "include.h"

namespace MemoryPool
{
    template<typename T>
    struct Chunk_depr {
        //you can allocate stack buffer. This would be as sort of a STL pmr
        T* m_ptr = nullptr;
        const size_t size;
        public:
        Chunk_depr(void* ptr, const size_t size): m_ptr(reinterpret_cast<T*>(ptr)), size(size) {};
    };
    class MemoryPool {
        public:
        struct Chunk {
            void* m_ptr = nullptr;
            size_t size = 0;
            Chunk(void* ptr, const size_t size): m_ptr(ptr), size(size) {};
        };
        template<typename T>
        class Ptr {
            T* m_ptr = nullptr;
            public:
            Ptr() = delete;
            Ptr(T* ptr): m_ptr(ptr) {};
            ~Ptr() {
                Delete();
            }
            void Delete() {
                //null ptr
                //decrease offset in memory pool
            };
            T operator*() {
                return *m_ptr;
            }
            void operator=(const T& t) {
                *m_ptr = t;
            }
        };
        private:
        size_t m_size = 0;
        void* m_pMemory = nullptr;
        size_t m_offset = 0;
        std::vector<Chunk> m_chunks = {};
        public:
        MemoryPool() = default;
        ~MemoryPool() {
            Deallocate();
        }
        bool Allocate(size_t size) {
            if (m_pMemory) {
                return false; }

            m_pMemory = std::malloc(size); //TODO: dont allocate with large size
            
            m_size = size;
            return true;
        };
        bool Deallocate() {
            if (m_pMemory) {
                std::free(m_pMemory);
                m_pMemory = nullptr; // Remember to free and null a pointer.
                m_size = 0;
                return true;
            }
            return false;
        };
        template<typename T>
        void* ReserveChunk() {
            size_t s = sizeof(T);
            if (!m_pMemory || m_size - m_offset < s) {
                return nullptr; }
            void* result = m_pMemory + m_offset;
            m_offset += s;
            m_chunks.emplace_back(Chunk(result, s));
            return result;
        };

        
    };
    template<typename T>
    MemoryPool::Ptr<T> New(MemoryPool& pPool) {
        MemoryPool::Ptr<T> ptr(reinterpret_cast<T*>(pPool.ReserveChunk<T>()));
        return ptr;
    };
    template<typename T>
    void Delete_depr(T& val) {
        static_assert(std::is_pointer_v<T>);
        //find chunk with pointer
        //mush chunk in pool
        val = nullptr;
    }
    void Test() {
        MemoryPool mp;
        if (mp.Allocate(100000000)) {
            auto chunk = New<short>(mp);
            auto chunk2 = New<int>(mp);
            auto vl = *chunk;
            chunk = 2;
            int in;
            std::cin >> in;
        }
    };
} // namespace MemoryPool
