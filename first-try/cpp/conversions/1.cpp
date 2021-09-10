#include <iostream>
#include <cstring>

using namespace std;

struct To {
    int b;    
};
 
struct From : public To {

    int a;
};
 
int main()
{
    From from;
    from.a = 2;

    To* to = static_cast<To*>(&from);

    cout << from.a << endl;
    cout << to->b << endl;

    return 0;
}

