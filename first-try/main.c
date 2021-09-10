#include <dlfcn.h>

void Foo();
void Bar1();

int main()
{
    void (*bar2_ptr)() =dlsym(dlopen("libso2.so", RTLD_LAZY), "Bar2");

    Foo();
    Bar1();
    bar2_ptr();
    
    
    return 0;
}
