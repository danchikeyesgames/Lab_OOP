#include "hexagon.h"

Hexagon::Hexagon(std::istream& ins)
{
    std::cin >> a_ >> b_ >> c_ >> d_;
    std::cin >> e_ >> f_;
}

size_t Hexagon::VertexesNumber()
{
    return (size_t)6;
}

double Hexagon::Area()
{
    return 0.5 * abs((a_.getX() * b_.getY() + b_.getX() * c_.getY() + c_.getX() * d_.getY() + d_.getX() * e_.getY() + e_.getX() * f_.getY() +
     - (b_.getX() * a_.getY() + c_.getX() * b_.getY() + 
    d_.getX() * c_.getY() + e_.getX() * d_.getY() + f_.getX() * e_.getY())));
}

void Hexagon::Print(std::ostream& ssd)
{
    std::cout << "Hexagon: " << a_ << " " << b_ << " ";
    std::cout << c_ << " " << d_ << " " << e_ << " ";
    std::cout << f_ << "\n";
}