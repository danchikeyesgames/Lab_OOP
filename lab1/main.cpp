#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

int main()
{

    Hexagon a(std::cin);
    Octagon b(std::cin);
    Triangle c(std::cin);

    a.Print(std::cout);
    b.Print(std::cout);
    c.Print(std::cout);

    return 0;
}