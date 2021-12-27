#ifndef TSTACKITEM_H
#define TSTACKITEM_H

#include <iostream>
#include <memory>

template <class T>
class TQueenItem
{
public:
    TQueenItem(const T &val, TQueenItem<T> *item);
    virtual ~TQueenItem();

    void Push(const T &val);
    T &Pop() const;
    void SetNext(TQueenItem<T> *item);
    TQueenItem<T> &GetNext() const;

private:
    T *value;
    TQueenItem<T> *next;
};

#endif