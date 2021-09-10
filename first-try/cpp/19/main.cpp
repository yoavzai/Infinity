#include <stdlib.h> // malloc

struct X
{
    X();
    ~X();
    int num;
};

struct Y
{
    Y();
    ~Y();
    int num;
};

X::X()
{}

X::~X()
{}

Y::Y()
{}

Y::~Y()
{}

int main()
{
    X* ptr = (X*)malloc(1000 * sizeof(X));
    delete ptr;
    /*Y* ptr2 = new Y[1000];
    free(ptr2);*/

    return 0;
}