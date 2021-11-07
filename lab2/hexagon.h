#ifndef HEXAGON_H
#define HEXAGON_H

#include "point.h"
#include "figure.h"

class hexagon : figure
{
public:
    hexagon(std::istream& is);
    hexagon();
    hexagon(Point a, Point b, Point c, Point d, Point e, Point f);


    size_t VertexesNumber();
    double Area();
    void Print(std::ostream& ssd);

    hexagon& operator=(const hexagon& other);
    bool operator==(hexagon& other);
    friend std::ostream& operator<<(std::ostream& os, hexagon& other);
    friend std::istream& operator>>(std::istream& is, hexagon& other);
private:
    Point a_, b_, c_;
    Point d_, e_, f_;
};

#endif
