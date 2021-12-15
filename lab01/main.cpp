#include <iostream>
#include <string.h>
class Racional
{
public:
    Racional() : numerator(0), denominator(0){};
    Racional(int a, int b) : numerator(a), denominator(b){};

    int get_num() const
    {
        return numerator;
    }

    int get_den() const
    {
        return denominator;
    }

    friend Racional operator+(const Racional &rac1, const Racional &rac2);
    friend Racional operator-(const Racional &rac1, const Racional &rac2);
    friend Racional operator*(const Racional &rac1, const Racional &rac2);
    friend Racional operator/(const Racional &rac1, const Racional &rac2);
    friend std::ostream &operator<<(std::ostream &out, const Racional &rac);
    friend std::istream &operator>>(std::istream &in, Racional &rac);

private:
    int numerator;
    int denominator;
    Racional reduce()
    {
        bool _end = false;
        for (int i = 2; i <= abs(this->numerator); i++)
        {
            while (this->numerator % i == 0 && this->denominator % i == 0)
            {
                this->numerator /= i;
                this->denominator /= i;
            }
        }
    }
};

std::ostream &operator<<(std::ostream &out, const Racional &rac)
{
    out << "Numerator is " << rac.get_num() << std::endl;
    out << "Denomirator is " << rac.get_den() << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Racional &rac)
{
    in >> rac.numerator;
    in >>rac.denominator;
    return in;
}

Racional operator+(const Racional &rac1, const Racional &rac2)
{
    Racional res(rac1.get_num() * rac2.get_den() + rac1.get_den() * rac2.get_num(), rac1.get_den() * rac2.get_den());
    res.reduce();
    return res;
};

Racional operator-(const Racional &rac1, const Racional &rac2)
{
    Racional res(rac1.get_num() * rac2.get_den() - rac1.get_den() * rac2.get_num(), rac1.get_den() * rac2.get_den());
    res.reduce();
    return res;
};

Racional operator*(const Racional &rac1, const Racional &rac2)
{
    Racional res(rac1.get_num() * rac2.get_num(), rac1.get_den() * rac2.get_den());
    res.reduce();
    return res;
};

Racional operator/(const Racional &rac1, const Racional &rac2)
{
    Racional res(rac1.get_num() * rac2.get_den(), rac1.get_den() * rac2.get_num());
    res.reduce();
    return res;
};

bool operator>(const Racional &rac1, const Racional &rac2)
{
    return (rac1.get_num() * rac2.get_den() - rac2.get_num() - rac1.get_den() > 0);
}

bool operator<(const Racional &rac1, const Racional &rac2)
{
    return (rac1.get_num() * rac2.get_den() - rac2.get_num() - rac1.get_den() < 0);
}

bool operator==(const Racional &rac1, const Racional &rac2)
{
    return (rac1.get_den() == rac2.get_den() && rac2.get_num() == rac2.get_den());
}

int main()
{
    Racional a;
    Racional b;
    //std::cout<<"Write first racional number: ";
    std::cin>>a;
    //std::cout<<"Write second racional number: ";
    std::cin>>b;
    std::cout<<"First number: \n"<<a<<std::endl;
    std::cout<<"Second number: \n"<<b<<std::endl;
    Racional c;
    c = a + b;
    std::cout << "Add: "<< c;
    c = a - b;
    std::cout << "Subtract: "<<c;
    c = a * b;
    std::cout << "Multiply: "<<c;
    c = a / b;
    std::cout << "Devide: "<< c;

    return 0;
}
