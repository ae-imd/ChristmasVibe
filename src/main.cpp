#include <iostream>
#include "../include/christmas.h"

int main()
{
    IMD::enable_color();
    IMD::println(IMD::christmas_tree(10));

    int num;
    std::cin >> num;

    return 0;
}