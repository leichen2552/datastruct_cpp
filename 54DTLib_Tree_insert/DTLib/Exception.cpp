#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace DTLib
{

void Exception::init(const char* message, const char* file, int line)
{
    m_message = (message ? strdup(message) : NULL); //这里是复制一份message
                                                    //因为这个message可能存在于栈上，也可能在全局数据区

//这里有bug,message可能是空指针，如果是空指针，strdup函数并未对输入的字符串是否合法做判断
//    m_message = strdup(message);//这里是复制一份message
//                                //因为这个message可能存在于栈上，也可能在全局数据区

    if(file != NULL)
    {
        char sl[16] = {0};

        itoa(line, sl, 10);

        m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
        m_location = strcpy(m_location, file);
        m_location = strcat(m_location, ":");
        m_location = strcat(m_location, sl);
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator= (const Exception& e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}

const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}

