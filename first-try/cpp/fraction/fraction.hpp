#ifndef _FRACTION_
#define _FRACTION_

#include <iostream>

namespace ilrd
{

class Fraction
{
public:
    explicit Fraction(int numer = 0, int denom = 1);
    Fraction(const Fraction& other);
    ~Fraction();
    void operator = (const Fraction& other);
    void operator += (const Fraction& other);
    void operator += (int num);
    bool operator == (const Fraction& other) const;
    bool operator == (int num) const;
    operator int() const;
    //operator double() const;
    Fraction operator + (const Fraction& other) const;
    Fraction operator - (const Fraction& other) const;
    Fraction operator + () const;
    Fraction operator - () const;
    Fraction& operator -- ();
    Fraction operator -- (int);
    Fraction& operator ++ ();
    Fraction operator ++ (int);
    bool IsUndefined() const;
    void Print() const;
    int GetNumer() const;
    int GetDenom() const;
    void SetNumer(int new_numer);
    void SetDenom(int new_denom);

    static size_t NumOfInstances();

private:
    static size_t n_instances;
    void Reduction();
    int numer;
    int denom; 
};

inline Fraction Fraction::operator + () const
{
    return Fraction(*this);
}

inline Fraction Fraction::operator - () const
{
    return Fraction(-numer, denom);
}

std::ostream& operator << (std::ostream& os, const Fraction& frac);

extern const Fraction ZERO;
extern const Fraction HALF;
extern const Fraction ONE;

}// namespace ilrd

#endif