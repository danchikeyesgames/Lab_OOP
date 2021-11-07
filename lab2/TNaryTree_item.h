#ifndef TNARYTREE_ITEM
#define TNARYTREE_ITEM

#include "hexagon.h"

class TreeItem
{
public:
    hexagon figure;
    int cur_size;
    TreeItem* son;
    TreeItem* brother;
    TreeItem* parent;
};

#endif
