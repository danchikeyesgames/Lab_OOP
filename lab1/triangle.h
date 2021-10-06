#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : Figure
{
public:
    Triangle(std::istream& ins);
    size_t Num();
    double Area();
    void Print(std::ostream& ssd);

private:
    Point a_;
    Point b_; 
    Point c_;
};

#endif