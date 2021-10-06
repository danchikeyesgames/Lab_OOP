#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"

class Figure
{
public:
    virtual size_t Num() = 0;
    virtual double Area() = 0;
    virtual void Print(std::ostream& ssd) = 0;
};

#endif