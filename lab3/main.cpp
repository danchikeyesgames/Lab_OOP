#include "figure.h"
#include "TNaryTree.h"
#include "TNaryTree_item.h"
#include "hexagon.h"
#include <string>

int main()
{
    TNaryTree a(4);
    if (a.Empty()) {
        std::cout << "The tree is empty !\n";
    } else {
        std::cout << "The tree is not empty !\n";
    }
    
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(1, 4), Point(1, 2), Point(5, 6), Point(2, 8),
    Point(3, 1), Point(2, 6))), ""); // 1
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(2, 5), Point(1, 5), Point(16, 6), Point(3, 6),
    Point(1, 8), Point(4, 2))), "c"); // 2
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(3, 5), Point(9, 1), Point(7, 3), Point(1, 8),
    Point(5, 6), Point(4, 8))), "cb"); // 3
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(8, 5), Point(1, 5), Point(16, 6), Point(3, 6),
    Point(1, 8), Point(4, 2))), "cbc"); // 4
    
    std::cout << a;
    std::cout << a.Area("cb") << "\n";
    TNaryTree b(a);
    std::cout << b;
    std::shared_ptr<hexagon> c = a.GetItem("");
    std::cout << *c;
    a.RemoveSubTree("cbc");
    
    if (a.Empty()) {
        std::cout << "The tree is empty !\n";
    } else {
        std::cout << "The tree is not empty !\n";
    }
    return 0;
}
