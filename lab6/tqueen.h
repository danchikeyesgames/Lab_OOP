#ifndef TSTACK_H
#define TSTACK_H

#include <iostream>
#include <memory>
#include "tqueen_item.h"

template <class T>
class TQueen
{
public:
    TQueen();
    virtual ~TQueen();
    void Push(const T &item);
    void Pop();
    T &Top();
    bool IsEmpty() const;
    uint32_t GetSize() const;
    template <class A> friend std::ostream& operator<<(std::ostream &os, const TQueen<A> &stack);

private:
    TQueenItem<T> *head;
    uint32_t count;
};

#endif