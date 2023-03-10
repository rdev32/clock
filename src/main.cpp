#include "clock.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char* argv[]) {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    Clock clock = Clock();
    clock.run();
    return 0;
}