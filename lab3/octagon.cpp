#include "octagon.h"
#include "point.h"

octagon::octagon(std::istream& is)
{
    std::cin >> a_ >> b_ >> c_ >> d_;
    std::cin >> e_ >> f_ >> g_ >> h_;
}

octagon::octagon() : a_(0,0), b_(0,0), c_(0,0), d_(0, 0), e_(0,0), f_(0,0), h_(0,0), g_(0, 0)
{}

octagon::octagon(Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h)
{
    this->a_ = a; this->b_ = b;
    this->c_ = c; this->d_ = d;
    this->e_ = e; this->f_ = f;
    this->h_ = h; this->g_ = g;
}

size_t octagon::VertexesNumber()
{
    return (size_t)8;
}

double octagon::Area()
{
    return 0.5 * abs((a_.getX() * b_.getY() + b_.getX() * c_.getY() + c_.getX() * d_.getY() + d_.getX() * e_.getY() + e_.getX() * f_.getY() +
    f_.getX() * g_.getY() + g_.getX() * h_.getY() + h_.getX() * a_.getY() - (b_.getX() * a_.getY() + c_.getX() * b_.getY() + 
    d_.getX() * c_.getY() + e_.getX() * d_.getY() + f_.getX() * e_.getY() + g_.getX() * f_.getY() + h_.getX() * g_.getY() +
    a_.getX() * h_.getY())));
}

octagon& octagon::operator=(const octagon& other)
{
    this->a_ = other.a_; this->b_ = other.b_;
    this->c_ = other.c_; this->d_ = other.d_;
    this->e_ = other.e_; this->f_ = other.f_;
    this->g_ = other.g_; this->h_ = other.h_;
    return *this;
}

bool octagon::operator==(octagon& other)
{
    return this->a_ == other.a_ && this->b_ == other.b_ &&
    this->c_ == other.c_ && this->d_ == other.d_ &&
    this->e_ == other.e_ && this->f_ == other.f_ &&
    this->g_ == other.g_ && this->h_ == other.h_;
}

std::ostream& operator<<(std::ostream& os, octagon& oct)
{
    os << "Octagon: " << oct.a_ << " " << oct.b_ << " ";
    os << oct.c_ << " " << oct.d_ << " " << oct.e_ << " ";
    os << oct.f_ << " " << oct.g_ << " " << oct.h_ << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, octagon& other)
{
    is >> other.a_ >> other.b_ >> other.c_ >> other.d_;
    is >> other.e_ >> other.f_ >> other.g_ >> other.h_;
    return is;
}

void octagon::Print(std::ostream& os)
{
    std::cout << "Octagon: " << a_ << " " << b_ << " ";
    std::cout << c_ << " " << d_ << " " << e_ << " ";
    std::cout << f_ << " " << g_ << " " << h_ << "\n";
}

octagon::~octagon(){}