#ifndef __CHRISTMAS_TREE_IMD_
#define __CHRISTMAS_TREE_IMD_

#include <cstddef>
#include <utility>
#include <iostream>
#include <random>

#define RESET "\033[0m"

namespace IMD
{

    constexpr std::pair<const char *, const char *> COLORS[] = {
        {"RED", "\033[31m"},
        {"GREEN", "\033[32m"},
        {"YELLOW", "\033[33m"},
        {"BLUE", "\033[34m"},
        {"MAGENTA", "\033[35m"},
        {"CYAN", "\033[36m"},
        {"WHITE", "\033[37m"},
        {"BRIGHT_RED", "\033[91m"},
        {"BRIGHT_GREEN", "\033[92m"},
        {"BRIGHT_YELLOW", "\033[93m"},
        {"BRIGHT_BLUE", "\033[94m"},
        {"BRIGHT_MAGENTA", "\033[95m"},
        {"BRIGHT_CYAN", "\033[96m"}};

    std::pair<const char *, const char *> get_random_color();

    const char *christmas_tree(size_t height);

    void print_color_tree(const char *tree, std::ostream &os = std::cout);
    void println_color_tree(const char *tree, std::ostream &os = std::cout);

    void enable_color();

}

#endif