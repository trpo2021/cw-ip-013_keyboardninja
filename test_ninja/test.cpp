#define CTEST_MAIN
#include <ctest.h>

#define CTEST_COLOR_OK
#define CTEST_SEGFAULT

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}
