#pragma once
#include <chrono>
#include <string>
#include "ExecutionTest.h"

class ICreateCompound_Algo;
class CopyByValueBase;
class CopyByPtrBase;

class BaseCopyCompoundTest
{

private:
    //Methods
    void AllocateArrays();
    void FillArrays();

protected:
    //Vars
    // array of pointers to arrays;
    uint64_t** arrays = nullptr;
    const size_t arrayCount = 0;
    const size_t arraySize = 0;
    std::chrono::microseconds result;
    std::string resultPrefix = "";
    ICreateCompound_Algo* copyToCompoundAlgo = nullptr;
    uint64_t** var = (arrays + 1);
    uint64_t element = *var[0];
    // int** arrays;
    // (int**)arrays + 0 = new int[100](int*)
    // (int**)arrays + 1 = new int[200](int*)
    // int** array1 = (arrays + 0)(int**)
    // int** array2 = (arrays + 1)(int**)
    // int* arrayElement = (array1 + 2)
    // int a1element0 = *(array1 + 0)
    // int a1element1 = *(array1 + 1)
    // int a2element0 = *(array2 + 0)
    // int a2element1 = *(array2 + 1)
    // *(array1 + 0) = 20
    // int* array = new int[100]
    // int element = *(array + 2)
    // *(array + 2) = 10
    //Const destr
    BaseCopyCompoundTest(size_t arrayCount, size_t arraySize);
    ~BaseCopyCompoundTest();

    //Interface
    virtual void AbstrRun() = 0;

    //Methods
    void BaseInit();
    void BaseRun();
    void BaseResultProcess();
};

// IExecutionTimeTest implementations

class CopyValueToCompoundTest_Impl final : public IExecutionTimeTest, public BaseCopyCompoundTest
{
private:
    uint64_t* copyCompound = nullptr;
    virtual void AbstrRun() override final;
    

    uint64_t* GetCopyCompound();
public:
    //CopyValueToCompoundTest_Impl(ICreateCompound_Algo* copyCompoundAlgo);

    CopyValueToCompoundTest_Impl(size_t arraySize, size_t arrayCount);
    ~CopyValueToCompoundTest_Impl();

    // Inherited via IExecutionTimeTest
    virtual void Init() override final;
    virtual void Run() override final;
    virtual void Shutdown() override final {};
    virtual void ProcessResult() override final;
};

class CopyPtrToCompoundTest_Impl final : public IExecutionTimeTest, public BaseCopyCompoundTest
{
private:
    uint64_t** ptrCompound = nullptr;
    virtual void AbstrRun() override final;
    

    uint64_t** GetPointerCompound();

public:
    //CopyPtrToCompoundTest_Impl(ICreateCompound_Algo* copyCompoundAlgo) {};
    CopyPtrToCompoundTest_Impl(size_t arraySize, size_t arrayCount);
    ~CopyPtrToCompoundTest_Impl();

    // Inherited via IExecutionTimeTest
    virtual void Init() override final;
    virtual void Run() override final;
    virtual void Shutdown() override final {};
    virtual void ProcessResult() override final;

};
//~IExecutionTimeTest implementations