#include <iostream>
#include <cstdlib> //system, rand, srand

#include "surpriser.hpp"

#define N_SURPRISES 3

namespace ilrd
{

Surpriser::Surpriser()
    : used(NULL)
{
}

Surpriser::~Surpriser()
{
    delete used;
}

void Surpriser::SurpriseMe()
{
}


class Surprise1 : public Surpriser
{
public:
    Surprise1();
    ~Surprise1() {}
    virtual void SurpriseMe()
    {
        std::cout << "Surprise!\n";
    }
};

Surprise1::Surprise1()
{
    Surpriser::used = this;
}

class Surprise2 : public Surpriser
{
public:
    Surprise2();
    ~Surprise2() {}
    virtual void SurpriseMe()
    {
        system("echo -e '\\a'");
    }
};

Surprise2::Surprise2()
{
    Surpriser::used = this;
}

class Surprise3 : public Surpriser
{
public:
    Surprise3();
    ~Surprise3() {}
    
    virtual void SurpriseMe()
    {
        system("echo file created");
    }
};

Surprise3::Surprise3()
{
    Surpriser::used = this;
}

typedef Surpriser* (*surpriser_func)();

Surpriser* Surprise_1()
{
    Surpriser* to_return = new Surprise1;
    return to_return;
}

Surpriser* Surprise_2()
{
    Surpriser* to_return = new Surprise2;
    return to_return;
}

Surpriser* Surprise_3()
{
    Surpriser* to_return = new Surprise3;
    return to_return;
}

surpriser_func arr[3] = {Surprise_1, Surprise_2, Surprise_3};

Surpriser* Surpriser::GetRandomSurprise()
{
    srand(time(NULL));

    return arr[rand() % N_SURPRISES]();
}

} //namespace ilrd