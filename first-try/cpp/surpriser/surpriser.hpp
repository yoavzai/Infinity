#ifndef _SURPRISER_
#define _SURPRISER_

namespace ilrd
{

class Surpriser
{
public:
    Surpriser();
    virtual ~Surpriser();
    static Surpriser* GetRandomSurprise();
    virtual void SurpriseMe();

    Surpriser* used; 
};

} //namespace ilrd

//#include "surpriser.cpp"

#endif
