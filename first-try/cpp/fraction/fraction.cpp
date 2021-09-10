#include <iostream>

#include "fraction.hpp"

using std::cout;
using std::endl;

namespace ilrd
{

const Fraction ZERO(0,1);
const Fraction HALF(1,2);
const Fraction ONE(1,1);

size_t Fraction::n_instances = 0;

Fraction::operator int() const
{
    return (numer / denom);
}   

//Fraction::operator double() const
//{
//    return (double(numer) / denom);
//}

std::ostream& operator << (std::ostream& os, const Fraction& frac)
{
    return (os << frac.GetNumer() << "/" << frac.GetDenom()); 
}

inline int Min(int a, int b)
{
    return a < b ? a : b;
}

size_t Fraction::NumOfInstances()
{
    return n_instances;
}

Fraction::Fraction(int numer, int denom) 
        : numer(numer), denom(denom)
{
    this->Reduction();
    n_instances++;
}

Fraction::Fraction(const Fraction& other)
{
    numer = other.numer;
    denom = other.denom;
    n_instances++;
}

Fraction::~Fraction()
{
    n_instances--;
}

void Fraction::Reduction()
{
    int sign = 1;

    if (numer < 0)
    {
        sign *= -1;
        numer *= -1;
    }

    if (denom < 0)
    {
        sign *= -1;
        denom *= -1;
    }

    unsigned int gcd = 1;
    int i = 1;
    int min = Min(numer, denom);

    while (i <= min)
    {
        if (numer % i == 0 && denom % i == 0)
        {
            gcd = i;
        }

        ++i;
    }

    numer /= gcd;
    numer *= sign;
    denom /= gcd;
}

void Fraction::operator = (const Fraction& other)
{
    numer = other.numer;
    denom = other.denom;
}

void Fraction::operator += (const Fraction& other)
{
    numer = numer * other.denom + other.numer * denom;
    denom *= other.denom;

    this->Reduction();
}

void Fraction::operator += (int num)
{
    Fraction other(num);

    *this += other;

    this->Reduction();
}

bool Fraction::operator == (const Fraction& other) const
{
    return (numer == other.numer) && (denom == other.denom);
}

bool Fraction::operator == (int num) const
{
    return (numer == num) && (denom == 1);
}

Fraction Fraction::operator + (const Fraction& other) const
{
    Fraction sum(*this);
    
    sum += other;

    return sum;
}

Fraction Fraction::operator - (const Fraction& other) const
{
    Fraction result(*this);
    
    result += -other;

    return result;
}

Fraction& Fraction::operator -- ()
{
    *this += -1;
    return *this;
}

Fraction Fraction::operator -- (int)
{
    Fraction to_return(*this);

    *this += -1;

    return to_return;

}

Fraction& Fraction::operator ++ ()
{
    *this += 1;
    return *this;
}

Fraction Fraction::operator ++ (int)
{
    Fraction to_return(*this);

    *this += 1;

    return to_return;
}

bool Fraction::IsUndefined() const
{
    return denom == 0;
}

void Fraction::Print() const
{
    cout << numer << "/" << denom << endl; 
}

int Fraction::GetNumer() const
{
    return numer;
}

int Fraction::GetDenom() const
{
    return denom;
}
void Fraction::SetNumer(int new_numer)
{
    numer = new_numer;

    this->Reduction();
}

void Fraction::SetDenom(int new_denom)
{
    denom = new_denom;
    this->Reduction();
}

}//namespace ilrd




