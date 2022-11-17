#include "include.h"
#include "globals.h"

#include "Stream.h"
#include "operators.h"
#include "template.h"
#include "FoldAnArray.hpp"
#include "MissingArithmeticProgression.hpp"
#include "pigIt.hpp"
#include "Extern.hpp"
#include "MemoryPool.hpp"
#include "Prototype.hpp"
#include "MbrWrapper.hpp"

//import mod;

void Welcome() {
    std::cout << gWelcomeStr << '\n';
};

namespace ExternTest {
    int ExternVar = 1;
    extern const int ConstExternVar = 2; //definition of const must be with explicit extern
};
namespace Unsorted {
    void StdMin() { //std::min's third params is just template method pattern. in that case "min" does mean nothing
        int a = 10;
        int b = 20;
        std::cout << std::min(a , b, [](int v1, int v2) { return v1 < v2; });
    };
    void MoveTest() {
        int a = 10; 
        int b = 20;
        a = std::move(b); //just copying because of && definition of function (?)
        std::cout << a;
    };
};
class InitClass {
    public:
    int a = 0;
    int b = 0;
    InitClass() : a(10), b{20} {}; // () or {}
    //InitClass() : a = 10 {}; // cannot use = 
};

#pragma region RvalueAndMove
    class Movebale {
        public:
        int* a = nullptr;
        Movebale(int* a) : a(a) {};
        ~Movebale() { delete a; };
        Movebale(Movebale&& other) { 
            this->operator=(other);
        };
        Movebale& operator=(const Movebale& other) = default;
        //std::move will cast any variable to && value so that ctor will be invoked.
        //notice that std::move doesn't mean moving of resource ownership. It depents only by definition.
        Movebale& operator=(Movebale&& other) { //dont use const qualifier to change other's ptr to null
            { //move ovnership
            this->a = other.a;
            other.a = nullptr;
            }
            return *this;
        };
    };
#pragma endregion

#pragma region CamelCaseTask
namespace CamelCaseTask {
    std::string to_camel_case(std::string text) {
        std::string cacheStr = "";
        std::string cacheWord = "";
        const auto size = text.size();

        auto toUpperChar_l = [](const char& ch) -> char {
            if (static_cast<uint32_t>(ch) > 90) { return ch - 32u; }
            else { return ch; }
        };
        auto toLowerChar_l = [](const char& ch) -> char {
            if (static_cast<uint32_t>(ch) < 91) { return ch + 32u; }
            else { return ch; }
        };
        auto saveChar_l = [&](const char& ch) { cacheWord += ch; };

        
        for (size_t i = 0; i < size; ++i) {
            char ch = text[i];
            if (ch == '-' || ch == '_' || i == size - 1) { //save word
                if (i == size - 1) { //save last char before saving word
                    if (cacheWord.size() == 0) { saveChar_l(toUpperChar_l(ch)); }
                    else { saveChar_l(toLowerChar_l(ch)); }
                }
                cacheStr += cacheWord;
                cacheWord = "";
                continue;
            }
            if (cacheWord.size() == 0) { 
                if (i == 0) { saveChar_l(ch); } //save first char without modification
                else { saveChar_l(toUpperChar_l(ch)); }
            }
            else {
                saveChar_l(toLowerChar_l(ch));
            }
        }
        return cacheStr;
    }
}
#pragma endregion

#pragma region TemplateTraits
    template<typename T>
    constexpr bool is_char_v = false;
    template<>
    constexpr bool is_char_v<char> = true;
#pragma endregion

#pragma region TemplateWithApercent
    template<typename T>
    void func1(T& t) {}; //f(int), T = int;
    template<typename T>
    void func1(T&& t) {}; //f(std::move(int)), T = int; f(int), T = int& reference collapsing
#pragma endregion

#pragma region StaticPolymorphism
    class Cat {
        public:
        void Speak() { std::cout << "Mew\n"; };
    };
    class Dog {
        public:
        void Speak() { std::cout << "Woof\n"; };
    };
    template<typename T>
    void AnimalDoubleSpeak(T& animal) {
        animal.Speak();
        animal.Speak();
    };
    template<typename T>
    class Animal {
        T* t = nullptr;
        public:
        Animal(T& other) { t = &other; };
        void DoubleSpeak() {
            t->Speak();
            t->Speak();
        }
    };
    void StaticPolTest() {
        Cat cat;
        Dog dog;
        //AnimalDoubleSpeak(dog);
        //AnimalDoubleSpeak(cat);
        Animal animal(dog); //deduced automaticaly
        animal.DoubleSpeak();
    };
#pragma endregion

#pragma region uniqueTest
using uniqueTestType = std::string;
void passUnique(const std::unique_ptr<uniqueTestType>& obj) {
    std::cout << *obj << '\n';
};
//dont use && in arg declaration if intend of function is not to take ownership. Because caller will do std::move with "move" in mind
void moveUnique(std::unique_ptr<uniqueTestType> obj) { // && still a refenrece. So if you pass std::move this doesnt move ownership,\
you need to leave unref argument to call it's && constructor
    //or create new unique ptr here and assign "obj" to it, it will move ownership
    *obj = "Bye";
    std::cout << *obj << '\n';
};
class TakesOnwership {
    std::unique_ptr<uniqueTestType> m_obj;
    public:
    void Take(std::unique_ptr<uniqueTestType>&& obj) {
        m_obj = std::move(obj); //obj is not valid for now
    };
    std::unique_ptr<uniqueTestType> Return() {
        return std::move(m_obj); //m_obj is not valid for now
    };
};
void uniqueTest() {
    using unique = std::unique_ptr<uniqueTestType>;
    auto print = [](const unique& obj) {std::cout << (obj ? *obj : "Empty") << '\n'; };
    
    unique t1(new uniqueTestType("Hello"));
    passUnique(t1);
    print(t1);
    moveUnique(std::move(t1));
    print(t1);

    unique t2(new uniqueTestType("t2"));
    print(t2);
    {
        TakesOnwership tO;
        tO.Take(std::move(t2)); //takes ownership and destroys
    }
    print(t2);

    unique t3(new uniqueTestType("t3"));
    print(t3);
    {
        TakesOnwership tO;
        tO.Take(std::move(t3));
        t3 = tO.Return(); //return ownership before dctor
    }
    print(t3);

    unique t4(new uniqueTestType("t4"));
    print(t4);
    TakesOnwership tO;
    tO.Take(std::move(t4)); //takes ownership
    print(t4);
};

#pragma endregion

#pragma region CountBits
namespace CountBits {
    unsigned int countBits(unsigned long long n){
        size_t count = 0;
        for (size_t i = 0; i < 64; ++i) {
            if (1u & n) { ++count; }
            n = n >> 1;
        }
        return count;
    }
    void Test () {
        std::cout << countBits(4);
    }
}
#pragma endregion

#pragma region sumParts
namespace sumParts //TODO: optimize;
{
    std::vector<unsigned long long> partsSum(const std::vector<unsigned long long>& ls){
        using vec = std::vector<unsigned long long>;

        size_t size = ls.size();
        std::vector<vec> compound(size);

        auto fillCompound = [&](const vec& array, size_t index) { compound[index] = array; };
        auto sumOfVecsInCompound = [&](size_t index) -> vec::value_type {
            size_t sum = 0;
            for (size_t i = 0; i < size - index; ++i) {
                sum += compound[i][index];
            }
            return sum;
        };
        auto reverseElementsInCompound = [&]() {
            for(size_t i = 0; i < size; ++i) {
                std::reverse(compound[i].begin(), compound[i].end());
            }
        };

        vec tempArr = ls; // for pop method //TODO: can I do std::move? if So, need to write a rule that passed ref to func must not be moved or something else
        std::reverse(std::begin(tempArr), std::end(tempArr)); //because I need to pop, later I will reverse back
        
        vec sum(size + 1); // 1 - for last "0" element
        
        //pop last element and pass to func
        for (size_t i = 0; i < size; ++i) {
            fillCompound(tempArr, i);
            tempArr.pop_back();
        }
        reverseElementsInCompound();
        for (size_t i = 0; i < size; ++i) {
            sum[i] = sumOfVecsInCompound(i);
        }
        return sum;
    }
    void Test() {
        auto vec = partsSum({0, 1, 3, 6, 10});
        //for (auto& el : vec) { std::cout << el << '\n'; }
    };
} // namespace sumParts

#pragma endregion

#pragma region pickPeaks //https://www.codewars.com/kata/5279f6fe5ab7f447890006a7/train/cpp //TODO: unfinished

namespace pickPeaks {
    struct PeakData {
        std::vector<int> pos, peaks;
    };
    using vec = std::vector<int>;

    PeakData pick_peaks(const std::vector<int> &v) {
        PeakData result{{},{}};
        const auto& size = v.size();
        //first and last elements cannot be a peak
        // peak is when prev. element is less than current and next is less to. Can be douplicats of value of peak, the first one is the peak
        // {1,2,2,1} 2 is peak
        // {1,2,2,3} no peak

        //PROTOTYPING
        size_t possiblePeakIndex = 0; // if next element is larger than previous, it will be marked as possible

        //walk by elements
        auto prevElement = v[0];

        for (auto i = 0u; i < size; ++i) {
            //if (i == 0 || i == size -1) //ignore
            auto& currentElement = v[i];
            const auto diff = currentElement - prevElement;
            if (diff > 0) {
                possiblePeakIndex = i;
                auto walk_l = [&]() -> bool {
                    for (auto j = possiblePeakIndex; j < size; ++j) { //TODO: ahead returning because of size - possiblePeak
                        auto& nextElement = v[j + 1];
                        auto& currentElement = v[j];
                        auto diff = currentElement - nextElement;
                        if ( diff > 0) { ++i; return true; } //peak. Next element cannot be a peak, so you must begin with next element?
                        if ( diff < 0) { return false; } //cancel peak
                        if ( diff == 0) { ++i; ++j; continue; } //resume peak
                    }
                    return false;
                };
                if(walk_l()) {
                    if (i == size) { break; }//lazy fix, can do better with less perf hit
                    result.pos.emplace_back(possiblePeakIndex);
                    result.peaks.emplace_back(v[possiblePeakIndex]);
                } else possiblePeakIndex = 0;
            }
            prevElement = currentElement;
        }
        return result;
    };
    void Test() {
        pick_peaks(std::vector<int> {1, 2, 2, 2, 1});
    };
};
#pragma endregion

#pragma region findOdd https://www.codewars.com/kata/54da5a58ea159efa38000836/train/cpp
namespace findOdd {
    int findOdd(const std::vector<int>& numbers){
        using intVec = std::vector<int>;

        auto size = numbers.size();
        std::vector<intVec> cacheOfElements;

        auto findOdd_l = [&]() -> int {
            using pair = std::pair<int, size_t>;
            
            std::vector<pair> sizeAndIndex; //size - index in cache

            int index = -1;
            for (const auto& vec : cacheOfElements) {
                ++index;
                if (vec.size() % 2 == 1) {
                    sizeAndIndex.emplace_back(vec[0], index);
                }
            }
            //find max size
            //auto maxEl = std::max_element(sizeAndIndex.begin(), sizeAndIndex.end());
            //int max = cacheOfElements[maxEl.operator*().second].at(0);
            return cacheOfElements[sizeAndIndex[0].second][0];
        };
        auto findNumber_l = [&](int toFind) -> int {
            int index = -1;
            for (const auto& vec : cacheOfElements) {
                ++index;
                if (vec[0] == toFind) { return index; }
            }
            return -1;
        };
        auto addNumber_l = [&](int number) {
            auto foundIndex = findNumber_l(number);
            if (foundIndex > -1) { cacheOfElements[foundIndex].emplace_back(number); }
            else { cacheOfElements.emplace_back(intVec{number}); }
        };

        if (size == 1) { return numbers[0]; }

        for (auto& el : numbers) {
            addNumber_l(el);
        }

        return findOdd_l();
    }
    void Test () {
        std::cout << findOdd({20,1,-1,2,-2,3,3,5,5,1,2,4,20,4,-1,-2,5}); //5
        std::cout << findOdd({1,1,2,-2,5,2,4,4,-1,-2,5}); //-1
        std::cout << findOdd({20,1,1,2,2,3,3,5,5,4,20,4,5}); //5
    };
}
#pragma endregion

#pragma region SimpleEncryption
namespace SimpleEncryption {
    using str = std::string;

    //true - odd, false - even
    template<bool type>
    str extractIndexed(const str& string) {
        str temp;
        int index = -1;
        for (auto& ch : string) {
            ++index;
            if constexpr (type) { if (index % 2) { temp += ch; } } //odd
            else { if (!(index % 2)) { temp += ch; } } //even
        }
        return temp;
    };

    std::string encrypt(std::string text, int n)
    {
        if (text.empty()) { return ""; }
        size_t repeatNum = n < 0 ? 0 : n;
        while (repeatNum > 0) {
            text = extractIndexed<true>(text) + extractIndexed<false>(text);
            --repeatNum;
        }
        return text;
    };
    //[1,2,3,4] [2,4,1,3] [4,3,2,1]
    std::string decrypt(std::string encryptedText, int n)
    {
        if (encryptedText.empty()) { return ""; }
        size_t repeatNum = n < 0 ? 0 : n;
        size_t size = encryptedText.size();

        auto divideString = [](const str& string) -> std::pair<str, str> {
            std::pair<str, str> divided;
            size_t stringSize = string.size();
            size_t leftSize = stringSize / 2;
            size_t rightSize = stringSize - leftSize;

            divided.first = string.substr(0, leftSize);
            divided.second = string.substr(rightSize - ((stringSize % 2) ? 1 : 0) ); // rs - 1 if remider of size division

            return divided;
        };

        auto decrypt_l = [&size](const std::pair<str, str>& parts) -> str {
            str temp;
            int doubleIndex = 0;
            for (size_t i = 0; i < size; ++i) {
                temp += !(i % 2) ? parts.second[doubleIndex] : parts.first[doubleIndex];
                if (i % 2) { ++doubleIndex; }
            }
            return temp;
        };
        str temp = encryptedText;

        for (size_t i = 0; i < repeatNum; ++i) {
            temp = decrypt_l(divideString(temp));
        }
        return temp;
    };
    void Test() {
        std::cout << encrypt("This is a test!", -1);
        std::cout << decrypt("hskt svr neetn!Ti aai eyitrsig", 1);
    };
}
#pragma endregion


void isNull() {
    //is q wiil be null?
    int* p = new int(10);
    int* q = p;
    delete p;
    p = nullptr;
    if (q) { printf("not null"); } //it is not null
    //so, any function that takes a ptr, stores not null even if the caller will delete the resource
    //TODO: save note: copying of pointers is crititcal restricted! because you cit's hard to trace how many thhem and who is the ownership

};

class FriendGlobalOperator {
    public:
    //you can define global operator within a class, istead of typing it elsewhere
    friend void operator==(FriendGlobalOperator, FriendGlobalOperator) {};
};

//comile time conversion?
/* template<class T, bool = std::is_arithmetic_v<T>>
constexpr std::string TypeToString(T Val) {
    return std::to_string(Val);
}; */

//signed/unsigned enums
enum class sError { succsess = 0, bad }; //signed
enum class uError { succsess = 0u, bad }; //unsigned


struct AccessOperator {
    int data = 0;
    //must return object, either copy or ptr
    auto operator->() { std::cout << "->\n"; return this; };
};


class ParentAccessSpecifier {
    public:
    class A {
        public:
        int data1 = 1; //acces is restricted in child class if one dirives with non public spec
        protected:
        int data2 = 2;
        private:
        int data3 = 3; //cannot be accesed even if child derives with private spec
    };
    class B : private A {
        public:
        B() { std::cout << data2 << '\n'; };
    };
};

namespace PointerToClassArrayTest {
    class A { public: int data = 0; };
    class B : public A {};
    void Test() {
        PointerToClassArrayTest::B b[] = {1,2,3,4,5,6};
        PointerToClassArrayTest::A* a = static_cast<PointerToClassArrayTest::A*>(b);
        for (auto i = 0ull; i < 6; ++i) {
            std::cout << a[i].data << '\n';
            std::cout << (a + i)->data << '\n';
        }
    }
};

namespace FunctionPointer {
    void func3(char arg) {};
    struct MemberFunctionPtr {
        int data = 0;
        void func(uint64_t arg) { std::cout << "MemberFunction " << arg << '\n'; };
    };
    void Test() {
        void (*pFunc)(char) = &FunctionPointer::func3; //ptr to function
        pFunc('b');

        // N. Ptr to member function\
        You cannot assign member function address to simple function pointer. You need to specify special decl\
        RTYPE (Class::*PTRNAME)(ARGTYPES)

        //void (*pMFunc)(uint64_t) = &FunctionPointer::MemberFunctionPtr::func; //error

        FunctionPointer::MemberFunctionPtr cls;
        FunctionPointer::MemberFunctionPtr cls2;
        int MemberFunctionPtr:: *varPtr = &MemberFunctionPtr::data;
        void (FunctionPointer::MemberFunctionPtr:: *funPtr)(uint64_t) = &FunctionPointer::MemberFunctionPtr::func;
        (cls.*funPtr)(1); //function call
        (cls2.*funPtr)(2); //function call
        cls.*varPtr; // variable 
    }
}

namespace ExplicitCtor {
    struct A {
        int data = 0;
    };
    struct B {
        int data = 1;
        explicit B(int data) : data(data) {};
    };
    void Test() {    
        ExplicitCtor::A a = {1};
        //ExplicitCtor::B b = {1}; //error, because of explicit ctor 
        ExplicitCtor::B b(1); //Ok
    }
}

namespace RestrictImplicitConversion {
    void func(int a) {};

    template<typename T>
    void func(T) = delete;
};

namespace ContigiousMemoryCompound {
    //Which struct will have no gap between arrays?
    struct TwoArraysStack {
        int array1[10];
        int array2[10];
    };
    struct TwoArraysHeap {
        int* array1 = new int[10];
        int* array2 = new int[10];
    };
    void Test() {
        
        auto loop_l = [](const int* arrPtr) {
            for (auto i = 0ull; i < 10; ++i) {
                std::cout << arrPtr + i << " - " << i << '\n';
            }
        };

        TwoArraysStack stack;
        loop_l(stack.array1);
        loop_l(stack.array2);

        TwoArraysHeap heap;
        loop_l(heap.array1);
        loop_l(heap.array2);

        if (&stack.array2[0] - &stack.array1[9] == 1) {
            std::cout << "stack pass\n";
        }
        
        if (&heap.array2[0] - &heap.array1[9] == 1) {
            std::cout << "heap pass\n";
        }
    };
};

namespace NonVirtualChild { //Virtual keyword is not required, but recommended
    struct A {
        virtual void func() { std::cout << "A\n"; };
    };
    struct B : A {
        void func() { std::cout << "B\n"; };
    };
};

namespace ExplicitCtorAndInitConversion {
    struct Expl {
        explicit Expl(int a) {};
    };
    struct Normal {
        Normal(int a) {};
    };
    void Test() {
        Expl a(10);
        //Expl a1 = 1; //conversion error, only explicit ctor
        Expl a2{10};
        //Expl a3{10.0}; //whether ctor is explicit or not, initalizer will emmit a error if narrowing is happen
        //Normal n1{10.0}; //narrowing error
        Normal n2 = 10; //implicit conversion
    };
};
namespace HierarchyCtor {
    struct A {
        A() { std::cout << "A\n"; };
    };
    struct B {
        B() { std::cout << "B\n"; };
    };
    //order of parent ctors corresponds to order of declaration
    struct C : B, A {
        C() : A(), B() { std::cout << "C\n"; }; //!!! ':' init will not override the order
    };
    void Test () {
        C c;
    };
};

namespace MemoryOperatorOverload {
    struct Object {
        Object() { std::cout << "Ctor\n"; };
        void* operator new(size_t){ std::cout << "Hello\n"; };
    };
    void Test () {
        MemoryOperatorOverload::Object* obj = new MemoryOperatorOverload::Object();
    };
};

auto VirtualOrPhysAddress_l = []() {
        int array[] = {1,2,3,4,5,6,7,8,9,10};
        int array2[] = {1,2,3,4,5,6,7,8,9,10};
        for (auto i = 0ull; i < 10; ++i) {
            std::cout << array + i << " - " << i << '\n';
        }
        for (auto i = 0ull; i < 10; ++i) {
            std::cout << array2 + i << '\n';
        }
    };


#define _TEST pigIt

int main() {

    /* LTK::StringStream stream;
    LTK::TestClass_1 cls1;
    stream << cls1;
    std::cout << stream.Get(); */

    /* LTK::OperatorTestClass o_1; o_1.data = 10;
    LTK::OperatorTestClass2 o2_1; o2_1.data = 30;
    LTK::OperatorTestClass2 o2_2; o2_2.data = 20;
    std::cout << (o2_1 + o2_2).data;
    std::cout << (o2_2 + o_1).data; */

    //std::vector<int> vec = {}; // init a vector

    MrbFactory::Test();

    int a = 0;
    const int ca = 0;
    int& ra = a;
    int* pa = &a;

    auto aa = a;
    auto aca = ca;
    auto ara = ra;
    auto apa = pa;

    auto apa = &a;
    auto apc = &ca;
    auto apra = &ra;
    auto appa = &pa;

    return 0;
}
