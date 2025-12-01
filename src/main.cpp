#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "../include/christmas.h"

int main()
{
    const size_t delay_ms(1000);

    IMD::enable_color();
    IMD::set_cursor_visibility(false);

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    IMD::clear_terminal();

    size_t amount(40);
    const char *heart = IMD::heart(8);
    while (amount != 0)
    {
        IMD::clrprintln(heart);
        --amount;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        IMD::move_cursor_home();
    }
    delete[] heart;

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    IMD::clear_terminal();

    amount = 40;
    const char *tree = IMD::tree(16);
    while (amount != 0)
    {
        IMD::clrprintln(tree);
        --amount;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        IMD::move_cursor_home();
    }
    delete[] tree;

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    IMD::clear_terminal();

    IMD::struct_snow_animation(40, 24, 10, 0.3, 15, 400);

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    IMD::clear_terminal();

    IMD::matrix_snow_animation(40, 24, 10, 0.3, 15, 400);

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    IMD::clear_terminal();

    IMD::set_cursor_visibility(true);
    std::cout << "Press any key" << std::endl;
    std::cin.get();

    return 0;
}