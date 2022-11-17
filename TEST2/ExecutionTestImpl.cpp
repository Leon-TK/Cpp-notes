#include "ExecutionTestImpl.h"
#include "CreateCompoundAlgoImpl.h"
#include <iostream>
void CopyValueToCompoundTest_Impl::AbstrRun()
{
    BaseCopyCompoundTest::copyToCompoundAlgo->Run();
}

CopyValueToCompoundTest_Impl::~CopyValueToCompoundTest_Impl()
{
    delete copyCompound;
}

uint64_t* CopyValueToCompoundTest_Impl::GetCopyCompound()
{
    const size_t compoundSize = arraySize * arrayCount;
    return new uint64_t[compoundSize];
}
//CopyValueToCompoundTest_Impl::CopyValueToCompoundTest_Impl(ICreateCompound_Algo* copyCompoundAlgo) : BaseCopyCompoundTest()
//{
//    BaseCopyCompoundTest::copyToCompoundAlgo = copyCompoundAlgo;
//}
CopyValueToCompoundTest_Impl::CopyValueToCompoundTest_Impl(size_t arraySize, size_t arrayCount): BaseCopyCompoundTest(arrayCount, arraySize)
{
}
void CopyValueToCompoundTest_Impl::Init()
{
    BaseCopyCompoundTest::resultPrefix = "CopyValueToCompoundTest duration: ";
    //setup compounds
    copyCompound = GetCopyCompound();
    BaseCopyCompoundTest::copyToCompoundAlgo = new CopyByValueInSequence(copyCompound, arrays, arrayCount, arraySize);
}

void CopyValueToCompoundTest_Impl::Run()
{
    BaseRun();
    ProcessResult();
    Shutdown();
}

void CopyValueToCompoundTest_Impl::ProcessResult()
{
    BaseCopyCompoundTest::BaseResultProcess();
}

void CopyPtrToCompoundTest_Impl::AbstrRun()
{
    BaseCopyCompoundTest::copyToCompoundAlgo->Run();
}

CopyPtrToCompoundTest_Impl::~CopyPtrToCompoundTest_Impl()
{
    //TODO delete inners?
    delete ptrCompound;
}

uint64_t** CopyPtrToCompoundTest_Impl::GetPointerCompound()
{
    const size_t compoundSize = arraySize * arrayCount;
    return new uint64_t * [compoundSize];
}
CopyPtrToCompoundTest_Impl::CopyPtrToCompoundTest_Impl(size_t arraySize, size_t arrayCount) : BaseCopyCompoundTest(arrayCount, arraySize)
{
    
}
void CopyPtrToCompoundTest_Impl::Init()
{
    BaseCopyCompoundTest::resultPrefix = "CopyPtrToCompoundTest duration: ";
    ptrCompound = GetPointerCompound();
    BaseCopyCompoundTest::copyToCompoundAlgo = new CopyByPtrInSequence(ptrCompound, arrays, arrayCount, arraySize);

}

void CopyPtrToCompoundTest_Impl::Run()
{
    BaseRun();
    ProcessResult();
    Shutdown();
}

void CopyPtrToCompoundTest_Impl::ProcessResult()
{
    BaseCopyCompoundTest::BaseResultProcess();
}

void BaseCopyCompoundTest::AllocateArrays()
{
    arrays = new uint64_t *[arrayCount];
    for (size_t i = 0; i < arrayCount; i++)
    {
        arrays[i] = new uint64_t[arraySize];
    }
}
void BaseCopyCompoundTest::FillArrays()
{
    for (size_t i = 0; i < arrayCount; i++)
    {
        for (size_t j = 0; j < arraySize; j++)
        {
            arrays[i][j] = j;
        }
    }
}

BaseCopyCompoundTest::BaseCopyCompoundTest(size_t arrayCount, const size_t arraySize): arraySize(arraySize), arrayCount(arrayCount)
{
    BaseInit();
}

BaseCopyCompoundTest::~BaseCopyCompoundTest()
{

    for (size_t i = 0; i < arrayCount; i++)
    {
        delete arrays[i];
    }

    delete arrays;
}

void BaseCopyCompoundTest::BaseInit()
{
    //setup arrays
    AllocateArrays();
    FillArrays();
}

void BaseCopyCompoundTest::BaseRun()
{
    auto Start = std::chrono::high_resolution_clock::now();

    AbstrRun();

    auto End = std::chrono::high_resolution_clock::now();

    //need to set it to class variable and then child class will process it in ProcessResult func.
    result = std::chrono::duration_cast<std::chrono::microseconds>(End - Start);
}

void BaseCopyCompoundTest::BaseResultProcess()
{
    std::cout << resultPrefix << result.count() << '\n';
}