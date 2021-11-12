#ifndef OCTAGON_H
#define OCTAGON_H

#include "point.h"
#include "figure.h"

class octagon : figure
{
public:
    octagon(std::istream& is);
    octagon();
    ~octagon();
    octagon(Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h);
    
    size_t VertexesNumber();
    double Area();
    void Print(std::ostream& os);

    octagon& operator=(const octagon& other);
    bool operator==(octagon& other);
    friend std::ostream& operator<<(std::ostream& os, octagon& other);
    friend std::istream& operator>>(std::istream& is, octagon& other);

private:
    Point a_, b_, c_, d_;
    Point e_, f_, g_, h_;
};

#endif