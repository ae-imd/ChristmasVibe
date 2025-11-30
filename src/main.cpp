#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "../include/christmas.h"

int main()
{
    IMD::setup_terminal();

    IMD::clear_terminal();
    size_t amount(10);
    const char *heart = IMD::heart(8);
    while (amount != 0)
    {
        IMD::clrprintln(heart);
        --amount;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        IMD::clear_terminal();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    delete[] heart;

    IMD::clear_terminal();
    amount = (10);
    const char *tree = IMD::tree(16);
    while (amount != 0)
    {
        IMD::clrprintln(tree);
        --amount;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        IMD::clear_terminal();
    }
    delete[] tree;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    IMD::clear_terminal();
    IMD::struct_snow_animation(40, 24, 0.3, 15, 400);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    IMD::clear_terminal();
    IMD::matrix_snow_animation(40, 24, 0.3, 15, 400);

    std::cin.get();

    return 0;
}