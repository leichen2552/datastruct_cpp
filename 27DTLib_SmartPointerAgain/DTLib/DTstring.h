#ifndef DTSTRING_H
#define DTSTRING_H

#include "Object.h"

namespace DTLib {

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l, const char* r, int len)const;

    static int* make_pmt(const char* p);
    static int kmp(const char* s, const char* p);
public:

    String();
    String(char c);
    String(const char* s);
    String(const String& s);

    int length() const;
    const char* str() const;

    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endof(const char* s) const;
    bool endof(const String& s) const;

    String& insert(int i, const char* s);
    String& insert(int i, const String& s);
    String& trim();//去掉两端的空格字符

    int indexof(const char* s) const;//判断是否有子串
    int indexof(const String& s) const;

    String& remove(int i, int len);
    String& remove(const char* s);
    String& remove(const String& s);

    char& operator [](int i);
    char operator [](int i)const;

    bool operator == (const String& s)const;
    bool operator == (const char* s)const;

    bool operator != (const String& s)const;
    bool operator != (const char* s)const;

    bool operator > (const String& s)const;
    bool operator > (const char* s)const;

    bool operator < (const String& s)const;
    bool operator < (const char* s)const;

    bool operator >= (const String& s)const;
    bool operator >= (const char* s)const;

    bool operator <= (const String& s)const;
    bool operator <= (const char* s)const;

    String operator +(const String& s)const;
    String operator +(const char* s)const;
    String& operator +=(const String& s);
    String& operator +=(const char* s);

    String operator -(const String& s)const;
    String operator -(const char* s)const;
    String& operator -=(const String& s);
    String& operator -=(const char* s);

    String& replace(const char* t, const char* s);
    String& replace(const String& t, const char* s);
    String& replace(const char* t, const String& s);
    String& replace(const String& t, const String& s);

    String sub(int i, int len)const;

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    ~String();
};

}



#endif // DTSTRING_H