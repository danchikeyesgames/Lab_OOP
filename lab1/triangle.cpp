#include "triangle.h"
#include "figure.h"
#include <math.h>

Triangle::Triangle(std::istream& ins)
{
    std::cin >> a_ >> b_ >> c_;
}

size_t Triangle::Num()
{
    return (size_t)3;
}

double Triangle::Area()
{
    double a = a_.dist(b_);
    double b = b_.dist(c_);
    double c = a_.dist(c_);
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

void Triangle::Print(std::ostream& ssd)
{
    std::cout << "Triangle: " << a_ << " " << b_ << " " << c_ << "\n";
}