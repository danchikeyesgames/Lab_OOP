#include <iostream>
#include <memory>
#include "tqueue_item.h"

template <class T>
TQueueItem<T>::TQueueItem(const T &val, TQueueItem<T> *item)
{
    value = new T(val);
    next = item;
}

template <class T>
void TQueueItem<T>::Push(const T &val)
{
    *value = val;
}

template <class T>
T &TQueueItem<T>::Pop() const
{
    return *value;
}

template <class T>
void TQueueItem<T>::SetNext(TQueueItem<T> *item)
{
    next = item;
}

template <class T>
TQueueItem<T> &TQueueItem<T>::GetNext() const
{
    return *next;
}

template <class T>
TQueueItem<T>::~TQueueItem()
{
    delete value;
}

template class
TQueueItem<void *>;