#pragma once
#include "CreateCompoundAlgo.h"
#include "stdint.h"
class CopyByValueBase
{
protected:
    //Const destr
    CopyByValueBase(uint64_t* compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
        : compound(compound), arrays(arrays), arrayCount(arrayCount), arraySize(arraySize)
    {
    }
    CopyByValueBase() = default;
    ~CopyByValueBase();

    //Vars
    uint64_t* compound = nullptr;
    uint64_t** arrays = nullptr;
    size_t arrayCount = 0;
    size_t arraySize = 0;

public:
    //Methods
    void SetParams(uint64_t* compound, uint64_t** arrays, size_t arrayCount, size_t arraySize);
};

class CopyByPtrBase
{
protected:
    //Const destr
    CopyByPtrBase(uint64_t** compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
        : compound(compound), arrays(arrays), arrayCount(arrayCount), arraySize(arraySize)
    {
    }
    ~CopyByPtrBase();

    //Vars
    uint64_t** compound = nullptr;
    uint64_t** arrays = nullptr;
    size_t arrayCount = 0;
    size_t arraySize = 0;

public:
    //Methods
    void SetParams(uint64_t** compound, uint64_t** arrays, size_t arrayCount, size_t arraySize);
};

// ICreateCompound_Algo implementations
class CopyByValueInSequence : public ICreateCompound_Algo, public CopyByValueBase
{
public:
    //Const destr
    CopyByValueInSequence(uint64_t* compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
        : CopyByValueBase(compound, arrays, arrayCount, arraySize)
    {
    }

    // Inherited via ICreateCompound_Algo
    virtual void Run() override final;
};

class CopyByValueSwitchArray : public ICreateCompound_Algo, public CopyByValueBase
{
public:
    //Const destr
    CopyByValueSwitchArray(uint64_t* compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
        : CopyByValueBase(compound, arrays, arrayCount, arraySize)
    {
    }

    // Inherited via ICreateCompound_Algo
    virtual void Run() override final;
};

class CopyByPtrInSequence : public ICreateCompound_Algo, public CopyByPtrBase
{
public:
    //Const destr
    CopyByPtrInSequence(uint64_t** compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
        : CopyByPtrBase(compound, arrays, arrayCount, arraySize)
    {
    }

    // Inherited via ICreateCompound_Algo
    virtual void Run() override final;
};
class CopyByPtrSwitchArray : public ICreateCompound_Algo, public CopyByPtrBase
{
public:
    //Const destr
    CopyByPtrSwitchArray(uint64_t** compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
        : CopyByPtrBase(compound, arrays, arrayCount, arraySize)
    {
    }

    // Inherited via ICreateCompound_Algo
    virtual void Run() override final;
};
//~ICreateCompound_Algo implementations
