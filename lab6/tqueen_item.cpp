#include <iostream>
#include <memory>
#include "tqueen_item.h"

template <class T>
TQueenItem<T>::TQueenItem(const T &val, TQueenItem<T> *item)
{
    value = new T(val);
    next = item;
}

template <class T>
void TQueenItem<T>::Push(const T &val)
{
    *value = val;
}

template <class T>
T &TQueenItem<T>::Pop() const
{
    return *value;
}

template <class T>
void TQueenItem<T>::SetNext(TQueenItem<T> *item)
{
    next = item;
}

template <class T>
TQueenItem<T> &TQueenItem<T>::GetNext() const
{
    return *next;
}

template <class T>
TQueenItem<T>::~TQueenItem()
{
    delete value;
}

template class
TQueenItem<void *>;