#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace DTLib
{

#define THROW_EXCEPTION(e,m) (throw e(m, __FILE__, __LINE__))


class Exception
{

protected:
    char* m_message;
    char* m_location;

    void init(const char* message, const char* file, int line);

public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator=(const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;//纯虚函数不需要函数体实现，纯虚函数等着子类来完成就行。但是这个地方是个例外
                             //但凡定义了析构函数，不 管他是不是虚函数，一定要提供实现，在析构一个对象的时候
                             //析构到最后总会到顶层，所以顶层父类的析构函数不管是不纯虚的，都要提供实现
};

//计算异常
class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception(0){}
    ArithmeticException(const char* message) : Exception(message){}
    ArithmeticException(const char* file, int line) : Exception(file, line){}
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line){}

    ArithmeticException(const ArithmeticException& e) : Exception(e){}

    ArithmeticException& operator =(const ArithmeticException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

//空指针异常
class NullPointerException : public Exception
{
public:
    NullPointerException() : Exception(0){}
    NullPointerException(const char* message) : Exception(message){}
    NullPointerException(const char* file, int line) : Exception(file, line){}
    NullPointerException(const char* message, const char* file, int line) : Exception(message, file, line){}

    NullPointerException(const NullPointerException& e) : Exception(e){}

    NullPointerException& operator =(const NullPointerException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

//越界异常
class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException() : Exception(0){}
    IndexOutOfBoundsException(const char* message) : Exception(message){}
    IndexOutOfBoundsException(const char* file, int line) : Exception(file, line){}
    IndexOutOfBoundsException(const char* message, const char* file, int line) : Exception(message, file, line){}

    IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e){}

    IndexOutOfBoundsException& operator =(const IndexOutOfBoundsException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

//内存不足异常
class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException() : Exception(0){}
    NoEnoughMemoryException(const char* message) : Exception(message){}
    NoEnoughMemoryException(const char* file, int line) : Exception(file, line){}
    NoEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line){}

    NoEnoughMemoryException(const NoEnoughMemoryException& e) : Exception(e){}

    NoEnoughMemoryException& operator =(const NoEnoughMemoryException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

//内存不足异常
class InvalidParameterException : public Exception
{
public:
    InvalidParameterException() : Exception(0){}
    InvalidParameterException(const char* message) : Exception(message){}
    InvalidParameterException(const char* file, int line) : Exception(file, line){}
    InvalidParameterException(const char* message, const char* file, int line) : Exception(message, file, line){}

    InvalidParameterException(const InvalidParameterException& e) : Exception(e){}

    InvalidParameterException& operator =(const InvalidParameterException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

}
#endif // EXCEPTION_H
