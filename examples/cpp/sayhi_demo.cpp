#include <sayhi/config.h>
#include <sayhi/sayhi.h>

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc > 0) {
        std::cout << "argc " << argc << " argv[0] " << argv[0] << std::endl;
    }

    sayhi::SayHi();

#ifdef SAYHI_USE_DEBUG
    std::cout << "sayhi_use_debug is true!" << std::endl;
#else
    std::cout << "sayhi_use_debug is false!" << std::endl;
#endif

    return 0;
}
