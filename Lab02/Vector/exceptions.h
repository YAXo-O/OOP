#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<exception>
#include<string>

class BaseException: public std::exception
{
public:
    BaseException(const std::string &errMsg)
    {
        errorMessage = errMsg;
    }

    virtual const char *what() const noexcept
    {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class AllocFail: public BaseException
{
public:
    AllocFail(const std::string &errMsg): BaseException(errMsg){}
};

class SizeMissmatch: public BaseException
{
public:
    SizeMissmatch(const std::string &errMsg): BaseException(errMsg){}
};

class OutOfRange: public BaseException
{
public:
    OutOfRange(const std::string &errMsg): BaseException(errMsg){}
};

class InvalidIterator: public BaseException
{
public:
    InvalidIterator(const std::string &errMsg): BaseException(errMsg){}
};

class DivisionZero: public BaseException
{
public:
    DivisionZero(const std::string &errMsg): BaseException(errMsg){}
};

class NonThreeD: public BaseException
{
public:
    NonThreeD(const std::string &errMsg): BaseException(errMsg){}
};

#endif // EXCEPTIONS_H
