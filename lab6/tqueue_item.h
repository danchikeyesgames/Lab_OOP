#ifndef TSTACKITEM_H
#define TSTACKITEM_H

#include <iostream>
#include <memory>

template <class T>
class TQueueItem
{
public:
    TQueueItem(const T &val, TQueueItem<T> *item);
    virtual ~TQueueItem();

    void Push(const T &val);
    T &Pop() const;
    void SetNext(TQueueItem<T> *item);
    TQueueItem<T> &GetNext() const;

private:
    T *value;
    TQueueItem<T> *next;
};

#endif