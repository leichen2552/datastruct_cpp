#ifndef LIST_H
#define LIST_H

namespace DTLib
{

template <typename T>
class List : public Object//这只是一个抽象类
{
public:
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
};

}


#endif // LIST_H
