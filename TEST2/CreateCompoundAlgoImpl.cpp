#include "CreateCompoundAlgoImpl.h"

void CopyByValueInSequence::Run()
{
    size_t compoundCounter = 0;

    for (size_t arrayCountCounter = 0; arrayCountCounter < arrayCount; arrayCountCounter++)
    {
        for (size_t arraySizeCounter = 0; arraySizeCounter < arraySize; arraySizeCounter++)
        {
            compound[compoundCounter] = arrays[arrayCountCounter][arraySizeCounter];
        }
        compoundCounter += 1;
    }
}

void CopyByValueSwitchArray::Run()
{
    size_t compoundCounter = 0;

    for (size_t arraySizeCounter = 0; arraySizeCounter < arraySize; arraySizeCounter++)
    {
        for (size_t arrayCountCounter = 0; arrayCountCounter < arrayCount; arrayCountCounter++)
        {
            compound[compoundCounter + arrayCountCounter] = arrays[arrayCountCounter][arraySizeCounter];
        }

        compoundCounter += arrayCount;
    }
}

void CopyByPtrInSequence::Run()
{
    size_t compoundCounter = 0;

    for (size_t arrayCountCounter = 0; arrayCountCounter < arrayCount; arrayCountCounter++)
    {
        for (size_t arraySizeCounter = 0; arraySizeCounter < arraySize; arraySizeCounter++)
        {
            compound[compoundCounter] = &arrays[arrayCountCounter][arraySizeCounter];
        }
        compoundCounter += 1;
    }
}

void CopyByPtrSwitchArray::Run()
{
    //need to increment by arraySize;
    size_t compoundCounter = 0;
    for (size_t arraySizeCounter = 0; arraySizeCounter < arraySize; arraySizeCounter++)
    {
        for (size_t arrayCountCounter = 0; arrayCountCounter < arrayCount; arrayCountCounter++)
        {
            compound[compoundCounter + arrayCountCounter] = &arrays[arrayCountCounter][arraySizeCounter];
        }
        compoundCounter += arrayCount;
    }
}

CopyByValueBase::~CopyByValueBase()
{
}
CopyByPtrBase::~CopyByPtrBase()
{
}

void CopyByValueBase::SetParams(uint64_t* compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
{
    this->compound = compound;
    this->arrays = arrays;
    this->arrayCount = arrayCount;
    this->arraySize = arraySize;
}

void CopyByPtrBase::SetParams(uint64_t** compound, uint64_t** arrays, size_t arrayCount, size_t arraySize)
{
    this->compound = compound;
    this->arrays = arrays;
    this->arrayCount = arrayCount;
    this->arraySize = arraySize;
}
