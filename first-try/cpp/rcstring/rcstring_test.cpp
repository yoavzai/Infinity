#include <iostream>

#include "rcstring.hpp"

using std::cout;
using std::endl;
using namespace ilrd;

inline void REQUIRE(bool one, bool two, int line)
{
    if (one == two)
    {
        cout << "Ok\n";
    }
    else
    {
        cout << "Problem at line " << line << endl;
    }
}

int main()
{
    RCString str1("hello");

    REQUIRE(str1 == "hello", true, __LINE__);
    REQUIRE(str1.IsShared(), false, __LINE__);
    REQUIRE(str1.Length() == 5, true, __LINE__);

    RCString str2(str1);

    REQUIRE(str2 == "hello", true, __LINE__);
    REQUIRE(str2.IsShared(), true, __LINE__);
    REQUIRE(str2.Length() == 5, true, __LINE__);

    {
        RCString str3 = "hello";

        REQUIRE(str3 == str1, true, __LINE__);
        REQUIRE(str3.IsShared(), false, __LINE__);
        REQUIRE(str3[4] == 'o', true, __LINE__);    
    }

    str2 = "bye";

    REQUIRE(str2 < str1, true, __LINE__);
    REQUIRE(str2.IsShared(), false, __LINE__);
    REQUIRE(str1.IsShared(), false, __LINE__);
    
    str1 = str2;

    REQUIRE(str1 != "hello", true, __LINE__);
    REQUIRE(str1.IsShared(), true, __LINE__);
    REQUIRE(str2.IsShared(), true, __LINE__);

    str1[2] = str2[0];
    str2[0] = 'e';

    REQUIRE(str1[2] == 'b', true, __LINE__);
    REQUIRE(str2[0] == 'e', true, __LINE__);
    REQUIRE(str1.IsShared(), false, __LINE__);
    REQUIRE(str2.IsShared(), false, __LINE__);


    return 0;
}