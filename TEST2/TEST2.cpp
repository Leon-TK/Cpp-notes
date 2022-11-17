#include <vector>
#include <chrono>
#include <iostream>
#include <cassert>
#include <tuple>
#include <cmath>
#include <string>
#include "ExecutionTest.h"
#include "ExecutionTestImpl.h"
#define assertm(exp, msg) assert(((void)msg, exp))
void TestCopyCompound(int* compound, size_t size)
{
    std::cout << "Copy compound last element " << compound[size - 1] << '\n';
};
void TestPtrCompound(int** compound, size_t size)
{
    std::cout << "Copy compound last element " << *(compound[size - 1]) << '\n';
};

void ChangeArrayElementToPointsNewElementInMemory_CLOSED()
{   //I'm trying to change pointer in array to point to other element in memory
    //Conclusion. Cannot change element of arr if arr doesn't contain pointers. CLOSED
    const int arrsize = 100;
    int* arr = new int[arrsize]; //returns 100 int*
    for (int i = 0; i < arrsize; i++)
    {
        arr[i] = i;
    }
    int element = *(arr + 2);//arr[2] // copy 2 element of array to element var
    element = arr[2]; //same
    assertm(element == arr[2] && element == *(arr + 2), "");
    *(arr + 2) = 100;//arr[2] //assign 100 to 2 lement of array
    arr[2] = 100;//same
    assertm(*(arr + 2) == 100 && arr[2] == 100, "");

    // try to assing new address.
     //COnclusion. Cant do that.
     //int* newelement = new int(666);
     //int* arrayElementPointer = arr + 2;
     //std::cout << arrayElementPointer << " " << (arr + 2) << '\n';
     //assertm(*arrayElementPointer == 100, "");
     //arrayElementPointer = newelement;
     //assertm(arrayElementPointer == newelement, "pointers are not equal");
     //assertm(*(arr + 2) == 666, "arr[2] has not been changed to newelement pointer");
     ////(arr + 1) = newelement;


    delete[] arr;
};

void ChangeArrayElementToPointsNewElementInMemory_PASS_ToOPTIMIZE()
{
    //I'm trying to change pointer in array to point to other element in memory

    //create array of pointers. elements are addresses to pointers.
    const int arraysize = 100;
    int** ptrArray = new int* [arraysize];

    /*When I create array of pointers and allocate variables to them by calling new int(val)
    it leads to unordered alligment of vars in memory. Instead you have to allocate array of vars by new int[count]
    and then get their adressesand assing to every pointer in array of poiters
    */
    //Initialize vars. Wrong way
    for (int i = 0; i < arraysize; i++)
    {
        //**(arr + i) = i;// first * -> int*, second * -> int from int* //undefined behavior because int* points to nothing, have to allocate memory before.
        *(ptrArray + i) = new int(i);
    }
    //~Initialize vars. Wrong way

    //Initialize vars. Right way
    //create array and assign its elements pointer to int** by iterating them
    int* orderedArray = new int[arraysize];
    //Init vars
    for (int i = 0; i < arraysize; i++)
    {
        orderedArray[i] = i;
    }

    //assing arr2 elements to inner arr pointers 
    for (size_t i = 0; i < arraysize; i++)
    {
        //TODO: I think when I access arr2 +i I need to do this by using (arr2 + i * elementsize)
        *(ptrArray + i) = (orderedArray + i); //equvalent to *&(arr2 + i) but uses more instructions
    }
    //~Initialize vars. Right way

    //Some test. I create elemet that points to var. When I change var it should change var in ptrArray
    int* element = *(ptrArray + 2);
    *element = 200;
    assertm(*element == 200, "Element hasnt been initialized");
    assertm(**(ptrArray + 2) == 200, "Array Element 2 hasnt been initialized");

    // Now change some pointer in array to point to somewhere new
    //This leads to unordered pointer items in memory
    //was -                 |||||||||
    //now -                 ||-||||||
    //new element somewhere   |
    int* newelement = new int(100);
    *(ptrArray + 2) = newelement;
    assertm(**(ptrArray + 2) == 100, "Array Element 2 hasnt been initialized to new element");

    delete[] ptrArray;
    delete newelement;
    //delete element;
};

void CreateArrayOfPointersWithOrderedElemetsInMemory_PASS_ToOPTIMIZE()
{
    //These steps are for ability to create array of arrays by using pointers in main array.

    //create array of pointers. elements are addresses to pointers.
    const int arraysize = 100;
    int** ptrArray = new int* [arraysize];

    /*When I create array of pointers and allocate variables to them by calling new int(val)
    it leads to unordered alligment of vars in memory. Instead you have to allocate array of vars by new int[count]
    and then get their adresses and assing to every pointer in array of pointers
    */
    //Initialize vars. Wrong way
    for (int i = 0; i < arraysize; i++)
    {
        //**(arr + i) = i;// first * -> int*, second * -> int from int* //undefined behavior because int* points to nothing, have to allocate memory before.
        *(ptrArray + i) = new int(i);
    }
    //~Initialize vars. Wrong way

    //Initialize vars. Right way
    //create new array and assign its elements pointer to int** by iterating them
    int* orderedArray = new int[arraysize];
    //Init vars
    for (int i = 0; i < arraysize; i++)
    {
        orderedArray[i] = i;
    }

    //assing arr2 elements to inner arr pointers 
    for (size_t i = 0; i < arraysize; i++)
    {
        //TODO: I think when I access arr2 +i I need to do this by using (arr2 + i * elementsize)
        *(ptrArray + i) = (orderedArray + i); //equvalent to *&(arr2 + i) but uses more instructions
    }
    //~Initialize vars. Right way

    //But what about allocating arrays instead of vars?//
    //How can I allocate 3 arrays with different var type in oerdered way like new int[count]?
    // Conclusion. So I can allocate arrays and then just...
    // Conclusion. I need custom allocator that overrides new operator. Before App start I need allocate big chunk of memory by calling stadard new operator.
    //Suppose I have arr1 of int type, arr3 of char type, arr4 of int64 type.
    // Main array have to contain arr1, arr2, arr3 in ordered way in memory
    // I cannot allocate it by new int[arr1.size+ arr2.size...]
    //I can create new struct with arr1, arr2, arr3. struct{int arr1; char arr2; int64 arr3;}
    //I can create void array - new void[arr1.size+ arr2.size...], but what next? TODO
    //Doubts! What if I need to allocate new element? I think its other story.
    /*Goal - Create new array from given old array for ECS Systems. For example Physics system needs location, collision components.
      Then program creates new array consists of 2 prevouis for cahce optimizing.cv
    */
    //Case 1. Struct.
    //Allocate struct, then elemets' addresses assing to main array to pointers
    struct CompoundRaw
    {
        CompoundRaw(int intSize, int charSize, int int64Size)
        {
            //This is wrong. Each allocating will allocate to different memory adfresses. I need to allocate these arrays in one aligment. TODO
            //
            intArray = new int[intSize];
            charArray = new char[charSize];
            int64Array = new uint64_t[int64Size];
            unsigned long long rawArraySize = sizeof(int) * intSize + sizeof(char) * charSize + sizeof(uint64_t) * int64Size;
            rawArray = new void* [rawArraySize]; //Array of void not allowed :(
        }

        void* rawArray; //this should be new void[sizeof intArray + sizeof charArray ...]

        int* intArray;
        char* charArray;
        uint64_t* int64Array;
    };

    //CompoundRaw* compoundRaw = new CompoundRaw();


};

template <typename T>
void AddForEach(T* t, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        t[i] += t[i];
    }
};
void bitCutTest()
{
    //Purpose. Test if bit cut from 64 register (on x86-64 ofcourse) to lower will be slower than not do cut. Test wich 8, 16, 32 are faster
    //Conclusion. Bit cut takes very small perf deceace and cache fullfilness is more major.
    //RESULTS millis
    //Size 100000000
    //149
    //77
    //36
    //18

    //RESULTS millis
    //Size 100000
    //46
    //29
    //8
    //3

    //RESULTS millis
    //Size 100
    //0.00013
    //0.00013
    //0.00013
    //0.00010

    //Average time after all iterations
    double averageByIterations[4]{ 0.0 };
    size_t iterCount = 20;

    constexpr size_t arraySize = 100;

    for (size_t i = 0; i < iterCount; i++)
    {
        std::cout << "Test " << i << '\n';

        ////Test 64
        {
            //Array of 64
            long long* a64 = new long long[arraySize] { 2 };
            auto start = std::chrono::high_resolution_clock::now();
            AddForEach(a64, arraySize);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            std::cout << "64: " << duration << '\n';
            delete[] a64;
            averageByIterations[0] += duration;
        }

        //Test 32 
        {
            //Array of 32
            int* a32 = new int[arraySize] { 2 };
            auto start = std::chrono::high_resolution_clock::now();
            AddForEach(a32, arraySize);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            std::cout << "32: " << duration << '\n';
            delete[] a32;
            averageByIterations[1] += duration;
        }
        //Test 16
        {
            //Array of 16
            short* a16 = new short[arraySize] { 2 };
            auto start = std::chrono::high_resolution_clock::now();
            AddForEach(a16, arraySize);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            std::cout << "16: " << duration << '\n';
            delete[] a16;
            averageByIterations[2] += duration;
        }
        //Test 8
        {
            //Array of 16
            char* a8 = new char[arraySize] { 2 };
            auto start = std::chrono::high_resolution_clock::now();
            AddForEach(a8, arraySize);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            std::cout << "8: " << duration << '\n';
            delete[] a8;
            averageByIterations[3] += duration;
        }

    }
    std::cout << "Avg 64: " << (averageByIterations[0] / iterCount) << '\n';
    std::cout << "Avg 32: " << (averageByIterations[1] / iterCount) << '\n';
    std::cout << "Avg 16: " << (averageByIterations[2] / iterCount) << '\n';
    std::cout << "Avg 8: " << (averageByIterations[3] / iterCount) << '\n';


};
//SoA_AoS_Test
namespace SoaAosTestOverComplicated
{
    struct Morpho
    {
        uint64_t id{ 0 };
    };

    class MorphoManager
    {
    private:
        size_t size { 0 };
        size_t upSize { 50 };
        Morpho* morphos {nullptr};
        size_t lastMorphoId{ 0 };

        void SetId(Morpho* m)
        {
            m->id = ++lastMorphoId;
        }

    public:
        MorphoManager() = default;

        Morpho* AddMorpho()
        {
            if (size == 0)
            {
                morphos = new Morpho[upSize];
                SetId(&morphos[0]);
                size++;
                return &morphos[0];
            }
            else
            {
                if (size != upSize) //whether trigger new array of morphos or not
                {
                    SetId(&morphos[size]);
                    size++;
                    return &morphos[size - 1];
                }
                else
                {
                    //Create new array because upSize is reached. Copy all old array's elements to new;
                    Morpho* newMorphos = new Morpho[size + upSize];
                    for (size_t i = 0; i < size; i++)
                    {
                        newMorphos[i] = morphos[i];
                    }
                    delete[] morphos;

                    morphos = newMorphos;
                    SetId(&morphos[size]);
                    size++;
                    return &morphos[size - 1];
                }
            }
        }
        void DeleteMorpho(Morpho* m)
        {
            if (m->id == 0)
            {
                return;
            }

            //find morpho
            for (size_t i = 0; i < size; i++)
            {
                if (morphos[i].id == m->id)
                {
                    morphos[i].id = 0;
                }
            }
        }
        Morpho* FindMorpho(size_t id)
        {
            if (id == 0)
            {
                return nullptr;
            }

            //find morpho
            for (size_t i = 0; i < size; i++)
            {
                if (morphos[i].id == id)
                {
                    return &morphos[i];
                }
            }
            return nullptr;
        }
    };
    
    class MorphoWorld
    {
    private:
        MorphoManager morphoManager;
    public:
        MorphoWorld() = default;

        Morpho* CreateMoprho()
        {
           return morphoManager.AddMorpho();
        }
        Morpho* FindMorpho(size_t id)
        {
            return morphoManager.FindMorpho(id);
        }
        void DeleteMorpho(Morpho* m)
        {
            morphoManager.DeleteMorpho(m);
        }
    };

    template <typename Archetype, int ComponentsCount>
    class SoA
    {
    private:
        size_t size{ 0 };
        Archetype* arr{ nullptr };
    public:
        SoA(size_t size) : size(size)
        {
            arr = new Archetype[size];
        };
    };
    template <typename Archetype>
    class AoS
    {
    private:
        size_t size { 0 };
        Archetype* arr { nullptr };
    public:
        AoS(size_t size) : size(size)
        {
            arr = new Archetype[size];
        };
    };
    //Purpose. Wanna test SoA and AoS. Wich one best suits certan goal

    //Components
    //A(int), B(int64), C(short)
    /*using A = int;
    using B = uint64_t;
    using C = short;*/
    template <typename Type>
    struct Component
    {
        Type type;
    };
    //Archetypes. It's a struct with certan combination of components.
    //A, B, C, A-B, A-C, B-C, A-B-C
    /*class Archetype
    {
    };*/
    template <typename ComponentType>
    struct ArchetypeData
    {
        //Array of components
        ComponentType* data;
    };
    struct A_B_Archetype
    {

        Component<int> a;
        Component<uint64_t> b;
        A_B_Archetype() = default;
    };

    struct A_C_Archetype
    {
        Component<int> a;
        Component<short> c;
        A_C_Archetype() = default;
    };

    void Test()
    {
        AoS<A_B_Archetype> abAos(100);
    };
};
namespace SoaAosTest
{
    //Components: A, B, C
    using A = short;
    using B = int;
    using C = uint64_t;
    //SoA
    template <size_t size>
    struct SoA_ABC
    {
        A a[size];
        B b[size];
        C c[size];
    };
    template <size_t size>
    struct SoA_AB
    {
        A a[size];
        B b[size];
    };
    template <size_t size>
    struct SoA_AC
    {
        A a[size];
        C c[size];
    };
    template <size_t size>
    struct SoA_BC
    {
        B b[size];
        C c[size];
    };
    template <size_t size>
    struct SoA_A_new
    {
        A* a = new A[size];
    };
    template <size_t size>
    struct SoA_A
    {
        A a[size];
    };
    struct SOA_A2
    {
        A* a;
        SOA_A2(size_t size)
        {
            a = new A[size];
        }
    };
    template <size_t size>
    struct SoA_B
    {
        B b[size];
    };
    template <size_t size>
    struct SoA_C
    {
        
        C c[size];
    };
    //AoS
    struct AoS_ABC_
    {
        A a;
        B b;
        C c;
    };
    struct AoS_AB_
    {
        A a;
        B b;
    };
    struct AoS_AC_
    {
        A a;
        C c;
    };
    struct AoS_BC_
    {
        B b;
        C c;
    };
    struct AoS_A
    {
        A a;
    };
    struct AoS_B
    {
        B b;
    };
    struct AoS_C
    {
        C c;
    };
    void AllocationTestForAllTypes()
    {
        using clock = std::chrono::high_resolution_clock;
        constexpr size_t SoaSize = 1000;
        constexpr size_t AosSize = 1000;

        auto SoaAllocationStart = clock::now();
        SoA_ABC<SoaSize>* sABC = new SoA_ABC<SoaSize>();
        SoA_AB<SoaSize>* sAB = new SoA_AB<SoaSize>();
        SoA_AC<SoaSize>* sAC = new SoA_AC<SoaSize>();
        SoA_BC<SoaSize>* sBC = new SoA_BC<SoaSize>();
        auto SoaAllocationEnd = clock::now();
        std::cout << "Soa alloc: " << std::chrono::duration_cast<std::chrono::microseconds>(SoaAllocationEnd - SoaAllocationStart).count() << '\n';
        //Soa alloc is slow

        auto AosAllocationStart = clock::now();
        AoS_ABC_* aABC = new AoS_ABC_[AosSize];
        AoS_AB_* aAB = new AoS_AB_[AosSize];
        AoS_AC_* aAC = new AoS_AC_[AosSize];
        AoS_BC_* aBC = new AoS_BC_[AosSize];
        auto AosAllocationEnd = clock::now();
        std::cout << "Aos alloc: " << std::chrono::duration_cast<std::chrono::microseconds>(AosAllocationEnd - AosAllocationStart).count() << '\n';
        //Aos alloc is fast
        
    }

    //Giving array of times calculate average time with threshold which cutting spikes in array of times. Threshold can be useful when you need cut off heap allocation spikes.
    //Add to iterationTimes the difference between end and start trace by each iteration in caller function
    double GetAvgTimeFromIterations(uint64_t* iterationTimes, size_t iterationsCount, float threshold = 1.f)
    {
        if (threshold > 1 || iterationTimes == nullptr)
        {
            return 0;
        }

        //calculate how much max values will be cutted
        size_t toCut = iterationsCount - double(ceil((float)iterationsCount * threshold));

        std::vector<size_t> maxValue(toCut);
        std::vector<size_t> maxIndexes(toCut);
        
        for (size_t i = 0; i < toCut; i++)
        {
            //find max values with given count to cut
            for (size_t j = 0; j < iterationsCount; j++)
            {
                //TODO check if value already in maxValue
                if (iterationTimes[j] > maxValue[i])
                {
                    bool alreadySaved = false;
                    for (size_t g = 0; g < maxValue.size(); g++)
                    {
                        if (maxValue[i] == iterationTimes[j])
                        {
                            alreadySaved = true;
                        }
                    }
                    if (alreadySaved)
                    {
                        continue;
                    }
                    else
                    {
                        maxIndexes[i] = j;
                        maxValue[i] = iterationTimes[j];
                    }
                }
            }
        }

        size_t timesCountWithoutMaxValues = iterationsCount - maxIndexes.size();

        double sum = 0;
        for (size_t i = 0; i < iterationsCount; i++)
        {
            bool isIndexMax = false;
            for (size_t j = 0; j < maxIndexes.size(); j++)
            {
                if (i == maxIndexes[j])
                {
                    isIndexMax = true;
                }
            }
            if (!isIndexMax)
            {
                sum += iterationTimes[i];
            }
            else
            {
                continue;
            }
            
        }

        return sum / timesCountWithoutMaxValues;
    }
    void AllocationTestForSimpleType()
    {
        //Test soa and aos with 1 type in

        //RESULT

        //SOA allocation soa of A type
        //template <size_t size>
        //struct SoA_A
        //{
        //    A a[size];
        //};
        //SoA_A<size>* sA = new SoA_A<size>();
        // 4000 micr
        
        //template <size_t size>
        //struct SoA_A
        //{
        //    A* a = new A[size];
        //};
        //SoA_A<size>* sA = new SoA_A<size>();
        // 50 micr

        //template <size_t size>
        //struct SoA_A
        //{
        //    A* a = new A[size];
        //};
        //SoA_A<size> sA;
        // 30 micr

        size_t iterCount = 20;
        using clock = std::chrono::high_resolution_clock;
        constexpr size_t size = 10000000;
        
        uint64_t* SoA_A_Sums = new uint64_t[iterCount] {0};
        uint64_t* SoA_A2_Sums = new uint64_t[iterCount] {0};
        uint64_t* AoS_A_Sums = new uint64_t[iterCount] {0};

        //test loop
        for (size_t i = 0; i < iterCount; i++)
        {
            //SoA_A template allocation
            auto SoaOneTypeStart = clock::now();
            SoA_A<size>* sA = new SoA_A<size>();
            auto SoaOneTypeEnd = clock::now();
            SoA_A_Sums[i] = std::chrono::duration_cast<std::chrono::microseconds>(SoaOneTypeEnd - SoaOneTypeStart).count();
            delete sA;

            //SoA_A2 allocation
            auto Soa2OneTypeStart = clock::now();
            SOA_A2* ssA = new SOA_A2(size);
            auto Soa2OneTypeEnd = clock::now();
            SoA_A2_Sums[i] = std::chrono::duration_cast<std::chrono::microseconds>(Soa2OneTypeEnd - Soa2OneTypeStart).count();
            delete ssA;

            //AoS_A allocation
            auto AosOneTypeStart = clock::now();
            AoS_A* aA = new AoS_A[size];
            auto AosOneTypeEnd = clock::now();
            AoS_A_Sums[i] = std::chrono::duration_cast<std::chrono::microseconds>(AosOneTypeEnd - AosOneTypeStart).count();
            delete[] aA;
        }
        
        std::cout << "SoA_A template one type alloc: " << GetAvgTimeFromIterations(SoA_A_Sums, iterCount, 0.8f) << '\n';
        std::cout << "SoA_A2 allocation one type alloc: " << GetAvgTimeFromIterations(SoA_A2_Sums, iterCount) << '\n';
        std::cout << "AoS_A allocation one type alloc: " << GetAvgTimeFromIterations(AoS_A_Sums, iterCount) << '\n';

        delete[] SoA_A_Sums;
        delete[] SoA_A2_Sums;
        delete[] AoS_A_Sums;
        
    }
}
#include <fstream>
//~SoA_AoS_Test
//NOTE: I should run each test separate because CPU architecture uses predictions in terms of cache optimizing
//Conclusions. Better to allocate small array count but with large content, otherwise allocations and freeing takes too much long time exec
//I dont know why, but ptr copy is less perfomant.
//I dont know why, but switch algo is faster. I toughted if I process copying by array it would decrease cache misses
int main()
{
    //case - Some system needs 30 components as compound component. Their size is 10 MB
    /*for (int i = 0; i < 5; i++)
    {
        IExecutionTimeTest* test = new CopyPtrToCompoundTest_Impl(10485760, 30);
        test->Init();
        test->Run();
        test->ProcessResult();
        test->Shutdown();
        delete test;
    }*/
    
    uint64_t arr[]{ 2,2,3,10,11 };
    std::cout << SoaAosTest::GetAvgTimeFromIterations(arr, 5, 0.6f);
 
    
    std::ofstream str("asdsad");
    ////test compounds
    //TestCopyCompound(copyCompound, arraySize * 3);
    //TestPtrCompound(ptrCompound, arraySize * 3);

    return 0;
};