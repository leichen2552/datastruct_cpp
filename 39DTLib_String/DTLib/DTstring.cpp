#include "DTstring.h"
#include <cstring>
#include <cstdlib>
#include "Exception.h"


namespace DTLib {

void String::init(const char *s)
{
    m_str = strdup(s);

    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create String object ... ");
    }

}

String::String()
{
    init("");
}


String::String(char c)
{
    char s[] = {c, '\0'};

    init(s);
}

String::String(const char* s)
{
    init(s ? s : "");//放置空指针，如果是空指针就转换为空字符串
}
String::String(const String& s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

bool String::operator == (const String& s)const
{
    return (strcmp(m_str, s.m_str) == 0);
}
bool String::operator == (const char* s)const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator != (const String& s)const
{
    return !(*this == s);
}
bool String::operator != (const char* s)const
{
    return !(*this == s);
}

bool String::operator > (const String& s)const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool String::operator > (const char* s)const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator < (const String& s)const
{
    return (strcmp(m_str, s.m_str) < 0);
}
bool String::operator < (const char* s)const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator >= (const String& s)const
{
    return (strcmp(m_str, s.m_str) >= 0);
}
bool String::operator >= (const char* s)const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator <= (const String& s)const
{
    return (strcmp(m_str, s.m_str) <= 0);
}

bool String::operator <= (const char* s)const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

String String::operator +(const String& s)const
{
    return (*this + s.m_str);
}
String String::operator +(const char* s)const
{
    String ret;

    int len = m_length + strlen(s ? s : "");

    char* str = reinterpret_cast<char*>(malloc(len + 1));

    if(str)
    {
        strcpy(str, m_str);     //拷贝m_str到申请的str中
        strcat(str, s ? s:"");  //字符串拼接，考虑s是否为空指针

        free(ret.m_str);        //释放掉m_str的内存

        ret.m_str = str;        //把处理完成的str重新赋值给m_str
        ret.m_length = len;     //重新赋值字符串长度
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No menory to add String values ...");
    }

    return ret;
}

String& String::operator +=(const String& s)
{
    return (*this = *this + s.m_str);
}
String& String::operator +=(const char* s)
{
    return (*this = *this + s);
}

String& String::operator = (const String& s)
{
    return (*this = s.m_str);
}
String& String::operator = (const char* s)
{
    if(m_str != s)
    {
        char* str = strdup(s ? s : "");//空指针当空字符串来处理

        if(str)
        {
            free(m_str);

            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No menory to assign new String values ...");
        }

    }

    return *this;
}
String& String::operator = (char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

String::~String()
{
    free(m_str);
}

}



