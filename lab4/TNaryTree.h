#ifndef TNARY_TREE
#define TNARY_TREE

#include "hexagon.h"
#include "TNaryTree_item.h"
#include <memory>

template<class T>
class TNaryTree
{
public:
    TNaryTree(int n);
    TNaryTree(const TNaryTree<T>& other);
    TNaryTree();

    void Update(const std::shared_ptr<T> &&polygon, const std::string &&tree_path)
    {
        Update(&root, polygon, tree_path);
    }

    void Update(const std::shared_ptr<T> &polygon, const std::string &tree_path)
    {
        Update(&root, polygon, tree_path);
    }

    const std::shared_ptr<T>& GetItem(const std::string& tree_path)
    {
        return GetItem(&root, tree_path);
    }

    void RemoveSubTree(const std::string &&tree_path);
    void RemoveSubTree(const std::string &tree_path);
    bool Empty();
    double Area(std::string&& tree_path);
    double Area(std::string& tree_path);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TNaryTree<A>& tree);
    virtual ~TNaryTree();

private:
    int size;
    std::shared_ptr<TreeItem<T>> root;
    void Update(std::shared_ptr<TreeItem<T>>* root, std::shared_ptr<T> polygon, std::string tree_path);
    const std::shared_ptr<T>& GetItem(std::shared_ptr<TreeItem<T>>* root, const std::string tree_path);
};

#endif