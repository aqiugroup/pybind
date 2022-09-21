#include <sayhi/sayhi.h>

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc > 0) {
        std::cout << "argc " << argc << " argv[0] " << argv[0] << std::endl;
    }

    SayHi();

    return 0;
}
