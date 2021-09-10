#include <stdio.h>
#include <dlfcn.h> /* dlopen */
#include <stdlib.h>


extern "C" {void Foo();}

int main(int argc, char* argv[])
{

    Foo();

    
    return 0;
}