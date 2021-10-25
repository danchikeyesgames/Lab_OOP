#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"

class Hexagon : Figure
{
public:
    Hexagon(std::istream& ins);
    size_t VertexesNumber();
    double Area();
    void Print(std::ostream& ssd);

private:
    Point a_, b_, c_;
    Point d_, e_, f_,;
};

#endif