#include "../include/clock.hpp"

#include <map>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string_view>

#ifdef __linux__ 
#include <sys/ioctl.h>
#elif _WIN32
#include <Windows.h>
#endif



Clock::Clock() {
    update();
    glyphs = std::map<char, std::vector<std::string_view>> {
        {'0', 
            {
                u8"▄▄▄▄▄ ",
                u8"█   █ ",
                u8"█ ▄▀█ ",
                u8"█▀  █ ",
                u8"▀▀▀▀▀ ",
            }
        },
        {'1', 
            {
                u8"▄▄▄   ",
                u8"  █   ",
                u8"  █   ",
                u8"  █   ",
                u8"▀▀▀▀▀ ",
            }
        },
        {'2', 
            {
                u8"▄▄▄▄▄ ",
                u8"    █ ",
                u8"█▀▀▀▀ ",
                u8"█     ",
                u8"▀▀▀▀▀ ",
            }
        },
        {'3',
            {
                u8"▄▄▄▄▄ ",
                u8"    █ ",
                u8"▀▀▀▀█ ",
                u8"    █ ",
                u8"▀▀▀▀▀ ",
            }
        },
        {'4', 
            {
                u8"▄   ▄ ",
                u8"█   █ ",
                u8"▀▀▀▀█ ",
                u8"    █ ",
                u8"    ▀ ",
            }
        },
        {'5', 
            {
                u8"▄▄▄▄▄ ",
                u8"█     ",
                u8"▀▀▀▀█ ",
                u8"    █ ",
                u8"▀▀▀▀▀ ",
            }
        },
        {'6',
            {
                u8"▄▄▄▄▄ ",
                u8"█     ",
                u8"█▀▀▀█ ",
                u8"█   █ ",
                u8"▀▀▀▀▀ ",
            }
        },
        {'7', 
            {
                u8"▄▄▄▄▄ ",
                u8"    █ ",
                u8"    █ ",
                u8"    █ ",
                u8"    ▀ ",
            }
        },
        {'8', 
            {
                u8"▄▄▄▄▄ ",
                u8"█   █ ",
                u8"█▀▀▀█ ",
                u8"█   █ ",
                u8"▀▀▀▀▀ ",
            }
        },
        {'9', 
            {
                u8"▄▄▄▄▄ ",
                u8"█   █ ",
                u8"▀▀▀▀█ ",
                u8"    █ ",
                u8"▀▀▀▀▀ ",
            }
        },
        {':', 
            {
                u8"     ",
                u8" ██  ",
                u8"     ",
                u8" ██  ",
                u8"     ",
            }
        },
    };
}

void Clock::display() {
    std::cout << u8"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    for (int row = 0; row < 5; ++row) {
        std::cout << u8"┃ ";
        for (const auto& digit : clock) {
            const auto& lines = glyphs.at(digit);
            std::cout << std::setw(5) << lines[row];
        }
        std::cout << u8" ┃\n";
    }
    std::cout << u8"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
}

void Clock::update() {
    auto time = std::time(nullptr);
    std::ostringstream format{};
    std::tm hour{};
    localtime_s(&hour, &time);
    format << std::put_time(&hour, "%H:%M:%S");
    clock = format.str();
}

void Clock::run() {
    while (true) {
        std::system("cls");
        update();
        display();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}