#pragma once

class IExecutionTimeTest
{
public:
    virtual void Init() = 0;
    virtual void Run() = 0;
    virtual void Shutdown() = 0;
    virtual void ProcessResult() = 0;
    virtual ~IExecutionTimeTest() {};
};

class IFunctionExecutionTime
{
public:
    virtual void Init() = 0;
    virtual void Run() = 0;
    virtual void Shutdown() = 0;
    virtual void ProcessResult() = 0;
    virtual ~IFunctionExecutionTime() {};
};

//~Execution time test Interface

