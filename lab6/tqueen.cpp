#include <iostream>
#include <memory>
#include "tqueen.h"

template <class T>
TQueen<T>::TQueen()
{
    head = nullptr;
    count = 0;
}

template <class T>
void TQueen<T>::Push(const T &item)
{
    TQueenItem<T> *tmp = new TQueenItem<T>(item, head);
    head = tmp;
    ++count;
}

template <class T>
bool TQueen<T>::IsEmpty() const
{
    return !count;
}

template <class T>
uint32_t TQueen<T>::GetSize() const
{
    return count;
}

template <class T>
void TQueen<T>::Pop()
{
    if(head) {
        TQueenItem<T> *tmp = &head->GetNext();
        delete head;
        head = tmp;
        --count;
    }
}

template <class T>
T &TQueen<T>::Top()
{
    return head->Pop();
}

template <class T>
TQueen<T>::~TQueen()
{
    for(TQueenItem<T> *tmp = head, *tmp2; tmp; tmp = tmp2) {
        tmp2 = &tmp->GetNext();
        delete tmp;
    }
}

template class
TQueen<void *>;