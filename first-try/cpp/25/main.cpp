#include <iostream>

namespace math
{
    long Fibo(int n) {return 0;}
    double Sin(double d) { return 0;}
    double Cos(double d) {return 0;}
}// namespace math

namespace fibonaci
{
    long lookupTable[256];
    long Fibo(int n) {return 0;}

    namespace altversion
    {
        long Fibo(size_t n) {return 0;}
    } // namespace altversion

} // namespace fibonaci

namespace math
{
    double Tang(double d) {return 0;}
} // namespace math

void A()
{
    int n = 3;
    fibonaci::Fibo(n);
    using math::Fibo;
    Fibo(n);

    math::Sin(3.14);
    math::Tang(3.14);
}

using namespace math;
using namespace fibonaci;
namespace alt=fibonaci::altversion;

void B()
{
    size_t n = 3;
    alt::Fibo(n);
    //Fibo(n); // try uncommenting this line, solve the error
    Cos(n); //why doesn't this line create an error?
}

int main()
{

    return 0;
}