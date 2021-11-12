#include "hexagon.h"
#include "TNaryTree_item.h"
#include <memory>

class TNaryTree
{
public:
    TNaryTree(int n);
    TNaryTree(const TNaryTree& other);
    TNaryTree();

    void Update(const std::shared_ptr<hexagon> &&polygon, const std::string &&tree_path)
    {
        Update(&root, polygon, tree_path);
    }

    void Update(const std::shared_ptr<hexagon> &polygon, const std::string &tree_path)
    {
        Update(&root, polygon, tree_path);
    }

    const std::shared_ptr<hexagon>& GetItem(const std::string& tree_path)
    {
        return GetItem(&root, tree_path);
    }

    void RemoveSubTree(const std::string &&tree_path);
    void RemoveSubTree(const std::string &tree_path);
    bool Empty();
    double Area(std::string&& tree_path);
    double Area(std::string& tree_path);
    friend std::ostream& operator<<(std::ostream& os, const TNaryTree& tree);
    virtual ~TNaryTree();

private:
    int size;
    std::shared_ptr<TreeItem> root;
    void Update(std::shared_ptr<TreeItem>* root, std::shared_ptr<hexagon> polygon, std::string tree_path);
    const std::shared_ptr<hexagon>& GetItem(std::shared_ptr<TreeItem>* root, const std::string tree_path);
};

