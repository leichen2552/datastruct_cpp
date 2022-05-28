#include "DTstring.h"
#include <cstring>
#include <cstdlib>
#include "Exception.h"


namespace DTLib {

int* String::make_pmt(const char* p) //O(m)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if( ret != NULL )
    {
        int ll = 0;

        ret[0] = 0;

        for(int i=1; i<len; i++)
        {
            while( (ll > 0) && (p[ll] != p[i]) )//直到ll等于0就跳出循环
            {
                ll = ret[ll-1];
            }

            if( p[ll] == p[i] )//最理想的情况，如果第一个字符等于最后一个字符，那么ll直接自加1
            {
                ll++;
            }

            ret[i] = ll;//那么这个时候，ll值存在部分匹配表里面
        }
    }

    return ret;
}

int String::kmp(const char* s, const char* p) //O(n)，比朴素算法O(m*n)强很多
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = make_pmt(p);


    //pmt不等于空
    //子串长度必须要大于0，不然毫无意义
    //字串长度小于目标串长度
    if( (pmt != NULL) && (0 < pl) && (pl <= sl))
    {
        for(int i=0,j=0; i<sl; i++)
        {
            while( (j > 0) && (s[i] != p[j]) )//如果匹配不成功，就去找部分匹配表，直到j==0为止跳出循环
            {
                j = pmt[j-1];
            }

            if(s[i] == p[j])//匹配成功
            {
                j++;
            }

            if(j == pl)
            {
                ret = i + 1 - pl;//返回字符串的起始下标
                break;
            }
        }
    }

    return ret;
}

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

bool String::equal(const char* l, const char* r, int len)const
{
    bool ret = true;

    for(int i=0; i<len && ret; i++)
    {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

bool String::startWith(const char* s)const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str, s, len);

    }

    return ret;
}
bool String::startWith(const String& s)const
{
    return startWith(s.m_str);
}

bool String::endof(const char* s)const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = strlen(s);
        char* str = m_str + (m_length - len);

        ret = (len < m_length) && equal(str, s, len);
    }

    return ret;
}
bool String::endof(const String& s) const
{
    return endof(s.m_str);
}

String& String::insert(int i, const char* s)
{
    if( (0 <= i) && (i < m_length) )
    {
        if((s != NULL)&&(s[0] != '\0'))
        {
            int len = strlen(s);
            char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));

            if(str != NULL)
            {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);

                str[m_length + len] = '\0';

                free(m_str);

                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert String value ... ");
            }

        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
    return *this;
}
String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;

    while (m_str[b] == ' ') {b++;}
    while (m_str[e] == ' ') {e--;}

    if(b == 0)
    {
        m_str[e + 1] = '\0';

        m_length = e + 1;
    }
    else
    {
        for(int i=0,j=b; j<=e; i++,j++ )
        {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }

    return *this;
}

int String::indexof(const char* s)const
{
    return kmp(m_str, s ? s : "");
}

int String::indexof(const String& s) const
{
    return kmp(m_str, s.m_str);
}

String& String::remove(int i, int len)
{
    if( ( 0<=i ) && (i < m_length) )
    {
        int n = i;
        int m = i + len;

        while( (n < m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }
        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
}

String& String::remove(const char* s)
{
    return remove(indexof(s), s ? strlen(s) : 0);
}

String& String::remove(const String& s)
{
    return remove(indexof(s), s.length());
}

String& String::replace(const char* t, const char* s)
{
    int index = indexof(t);

    if(index >= 0)
    {
        remove(t);
        insert(index, s);
    }

    return *this;
}

String& String::replace(const String& t, const char* s)
{
    return replace(t.m_str, s);
}

String& String::replace(const char* t, const String& s)
{
    return replace(t, s.m_str);
}

String& String::replace(const String& t, const String& s)
{
    return replace(t.m_str, s.m_str);
}

String String::sub(int i, int len)const
{
    String ret;

    if( (0 <= i) && (i < m_length) )
    {
        if(len < 0) len = 0;
        if(len + i > m_length) len = m_length - i;
        char* str = reinterpret_cast<char*>(malloc(len + 1));

        strncpy(str, m_str + i, len);

        str[len] = '\0';

        ret = str;//把申请的子串赋值给返回值对象

        //free(str);//我觉得需要释放，但是唐老师没有释放
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invaid ...");
    }


    return ret;
}

char& String::operator [](int i)
{
    if((0<=i) && (i<m_length))
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid");
    }
}

char String::operator [](int i)const
{
    return (const_cast<String&>(*this)[i]);
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

String String::operator -(const String& s)const
{
    return String(*this).remove(s);//产生临时对象跟当前的字符串对象是一样的，然后调用当前的临时对象的remove函数
}
String String::operator -(const char* s)const
{
    return String(*this).remove(s);//产生临时对象跟当前的字符串对象是一样的，然后调用当前的临时对象的remove函数
}

String& String::operator -=(const String& s)
{
    return remove(s);
}
String& String::operator -=(const char* s)
{
    return remove(s);
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



