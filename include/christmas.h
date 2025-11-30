#ifndef __CHRISTMAS_TREE_IMD_
#define __CHRISTMAS_TREE_IMD_

#include <cstddef>
#include <utility>
#include <iostream>
#include <random>

namespace IMD
{
    using color = std::pair<const char *, const char *>; // name, code

    constexpr color COLORS[] = {
        {"RESET", "\033[0m"}, // 0-index is ALWAYS RESET
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

    color get_random_color();

    const char *tree(size_t height, char symbol = '*');
    const char *heart(size_t size, char symbol = '*');

    void struct_snow_animation(size_t width, size_t height, double spawn_prob, size_t dur_secs, size_t max_amount, std::ostream &os = std::cout);
    void matrix_snow_animation(size_t width, size_t height, double spawn_prob, size_t dur_secs, size_t max_amount, std::ostream &os = std::cout);

    void clrprint(const char *tree, char symbol = '*', std::ostream &os = std::cout);
    void clrprintln(const char *tree, char symbol = '*', std::ostream &os = std::cout);

    void delprint(const char *line, size_t delay_ms, std::ostream &os = std::cout);
    void delprintln(const char *line, size_t delay_ms, std::ostream &os = std::cout);

    void setup_terminal();
    void clear_terminal();
}

#endif