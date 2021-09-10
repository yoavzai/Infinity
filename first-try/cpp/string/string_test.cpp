#include <iostream>

#include "string.hpp"

using std::cout;
using std::endl;
using namespace ilrd;

#define RED "\033[22;31m"
#define GREEN "\033[22;32m"
#define RESET "\x1B[0m"
#define REQUIRE(x,y) (x) == (y) ? PrintSuccess() : PrintFail()

static void PrintSuccess()
{
    cout << GREEN "SUCCESS\n" RESET;
}

static void PrintFail()
{
    cout << RED "FAIL\n" RESET;
}

int main()
{
    char str[] = "zaidenberg";

    String s1("yoav");
    String s2(str);

    REQUIRE(s1 == s2, false);
    REQUIRE(s1 < s2, true);
    REQUIRE(s1 > s2, false);
    REQUIRE(s1.Length(), 4);
    REQUIRE(s2, str);
    REQUIRE("yoav", s1);

    cout << s1 << " " << s2 << endl;

    String yoav = s1;
    String tomer = "tomer";
    s1 = str;

    cout << tomer << " " << yoav << endl;

    REQUIRE(str, s1);
    REQUIRE(yoav > tomer, true);

    return 0;
}