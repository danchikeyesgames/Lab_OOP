#ifndef TNARYTREE_ITEM
#define TNARYTREE_ITEM

#include "hexagon.h"
#include <memory>

class TreeItem
{
public:
    std::shared_ptr<hexagon> figure;
    int cur_size;
    std::shared_ptr<TreeItem> son;
    std::shared_ptr<TreeItem> brother;
    std::shared_ptr<TreeItem> parent;
};

#endif
