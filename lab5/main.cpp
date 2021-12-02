#include "TNaryTree.h"
#include "hexagon.h"
#include "titerator.h"
#include "TNaryTree_item.h"
#include <string>

int main()
{
    TNaryTree<hexagon> a(4);
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
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(4, 4), Point(1, 2), Point(5, 6), Point(2, 8),
    Point(3, 1), Point(2, 6))), "cbb"); // 4
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(5, 5), Point(1, 5), Point(16, 6), Point(3, 6),
    Point(1, 8), Point(4, 2))), "cbbc"); // 5
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(6, 5), Point(9, 1), Point(7, 3), Point(1, 8),
    Point(5, 6), Point(4, 8))), "cc"); // 6
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(7, 4), Point(1, 2), Point(5, 6), Point(2, 8),
    Point(3, 1), Point(2, 6))), "ccb"); // 7
    a.Update(std::shared_ptr<hexagon>(new hexagon(Point(8, 5), Point(1, 5), Point(16, 6), Point(3, 6),
    Point(1, 8), Point(4, 2))), "cbc"); // 8
    // a.Update(std::shared_ptr<hexagon>(new hexagon(Point(9, 5), Point(9, 1), Point(7, 3), Point(1, 8),
    // Point(5, 6), Point(4, 8), Point(9, 5), Point(6, 4))), "cbcb"); // 9
    // a.Update(std::shared_ptr<hexagon>(new hexagon(Point(10, 5), Point(9, 1), Point(7, 3), Point(1, 8),
    // Point(5, 6), Point(4, 8), Point(9, 5), Point(6, 4))), "ccc"); // 10
    // a.Update(std::shared_ptr<hexagon>(new hexagon(Point(11, 5), Point(9, 1), Point(7, 3), Point(1, 8),
    // Point(5, 6), Point(4, 8), Point(9, 5), Point(6, 4))), "cccb"); // 11
    for (auto i: a) {
        std::cout << *i << std::endl;
    }
    std::cout << a;
    std::cout << a.Area("cb") << "\n";
    TNaryTree<hexagon> b(a);
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
