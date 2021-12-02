#include "TNaryTree_item.h"

template<class T>
std::shared_ptr<TreeItem<T>> TreeItem<T>::GetNext()
{
    if (this->son != nullptr) {
        return this->son;
    }
    if (this->brother != nullptr) {
        return this->brother;
    }
    std::shared_ptr<TreeItem<T>> cur = this->parent;
    if (cur->brother != nullptr) {
        return cur->brother;
    }
    return nullptr;
}

#include "hexagon.h"
template class TreeItem<hexagon>;