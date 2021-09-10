#include <algorithm>
#include <iostream>

#include "bits_arr.hpp"

using std::cout;
using std::endl;
using std::hex;
using namespace ilrd;

#define N_BITS 128

inline void REQUIRE(bool x, bool y, unsigned int line)
{
    if (x == y)
    {
        cout << "ok\n";
    }

    else
    {
        cout << "problem at line " << line << endl;
    }   
}


int main()
{
    BitsArray<N_BITS> ba1;
    BitsArray<N_BITS> ba2(ba1);
    BitsArray<N_BITS> ba3 = ba2;

    REQUIRE(ba1 == ba2, true, __LINE__);
    REQUIRE(ba2 == ba3, true, __LINE__);
    REQUIRE(ba3 != ba1, false, __LINE__);
    REQUIRE(ba1.Count(true) == 0, true, __LINE__);
    REQUIRE(ba1.Count(false) == N_BITS, true, __LINE__);

    ba1 ^= ba2;

    REQUIRE(ba1 == ba2, true, __LINE__);

    ba1.SetAll();
    ba3.ToggleAll();

    REQUIRE(ba1 == ba3, true, __LINE__);
    REQUIRE(ba1 != ba2, true, __LINE__);
    REQUIRE(ba1.Count(true) == N_BITS, true, __LINE__);
    REQUIRE(ba1.Count(false) == 0, true, __LINE__);

    ba2.ToggleOne(100);

    REQUIRE(ba2.Count(true) == 1, true, __LINE__);
    REQUIRE(ba2.GetBit(100) == true, true, __LINE__);

    ba2[99] = ba2[100];
    ba2[98] = true;

    REQUIRE(ba2.Count(true) == 3, true, __LINE__);
    REQUIRE(ba2.GetBit(99) == true, true, __LINE__);
    REQUIRE(ba2.GetBit(98) == true, true, __LINE__);

    ba1.SetBit(100, false);

    REQUIRE(ba1.Count(false) == 1, true, __LINE__);
    REQUIRE(ba1.GetBit(100) == false, true, __LINE__);
    REQUIRE(static_cast< const BitsArray<N_BITS> >(ba1)[100] == false, true, __LINE__);
    REQUIRE(static_cast< const BitsArray<N_BITS> >(ba1)[127] == true, true, __LINE__);

    return 0;
} 