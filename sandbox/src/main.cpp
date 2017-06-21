#include <iostream>

//TODO(pangt): rename the 'src' to something
#include "kurobako\src\enginemain.h"

int main()
{
    kurobako::engine::InitEngine();
    std::cout << "Hello World!" << std::endl;
}