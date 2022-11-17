#pragma once

#ifdef PRIVATESUBS
    #define private public
#endif

namespace LTK {
    template <typename T>
    //TODO:: delete copy things
    class Unique {
        private:
        Unique();
        T* obj = nullptr;
        public:
        Unique(Unique&& rhv) {
            this->obj = rhv.obj;
            rhv.obj = nullptr;
        };
        Unique(const Unique&) = delete;
        Unique& operator=(const Unique&) = delete;
        void operator=(const Unique&& rhv) {
            this->obj = rhv.obj;
            rhv.obj = nullptr;
        };
        ~Unique() { if (obj) { delete obj; } };
        Unique(T* type) : obj(type) {};
        T& Get() { 
            if (obj) { return *obj; }
            else { throw std::exception(); }
        };
    };
    template <typename T>
    class Shared {
        private:
        
        static size_t count;
        Shared();
        T* obj = nullptr;
        public:
        ~Shared() {
            if (Shared<T>::count == 1 && obj) { delete obj; }
            --Shared<T>::count;
        };
        Shared(T* type) : obj(type) {
            ++count;
        };
        Shared(const Shared& rhv) {
            this->obj = rhv.obj;
            ++Shared<T>::count;
        };

        Shared& operator=(const Shared& rhv) {
            this->obj = rhv.obj;
            ++Shared<T>::count;
            return *this;
        }

        T& Get() { 
            if (obj) { return *obj; }
            else { throw std::exception(); }
        };

    };
    template <typename T, typename... Targs>
    Unique<T> NewUnique(Targs... params) {
        return Unique<T>(new T(params...));
    };
    template <typename T, typename ... Targs>
    Shared<T> NewShared(Targs... params) {
        return Shared<T>(new T(params...));
    };
};

template<typename T>
size_t LTK::Shared<T>::count = 0;