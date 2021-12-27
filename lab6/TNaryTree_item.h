#ifndef TNARYTREE_ITEM
#define TNARYTREE_ITEM

#include "titerator.h"
#include <memory>

template<class T>
class TreeItem
{
public:

    std::shared_ptr<TreeItem<T>> GetNext();

    std::shared_ptr<T> figure;
    int cur_size;
    std::shared_ptr<TreeItem<T>> son;
    std::shared_ptr<TreeItem<T>> brother;
    std::shared_ptr<TreeItem<T>> parent;
};

#endif