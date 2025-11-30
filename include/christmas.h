#ifndef __CHRISTMAS_TREE_IMD_
#define __CHRISTMAS_TREE_IMD_

#include <cstddef>
#include <utility>
#include <iostream>
#include <random>

#define CLEAR "\033[2J\033[1;1H"

namespace IMD
{
    using color = std::pair<const char *, const char *>;    // name, code
    using lyric = std::tuple<const char *, size_t, size_t>; // line, delay between chars, general delay

    constexpr color COLORS[] = {
        {"RESET", "\033[0m"},
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

    const char *christmas_tree(size_t height);
    void struct_snow_animation(size_t width, size_t height, double spawn_prob, size_t dur_secs, size_t max_amount, std::ostream &os = std::cout);
    void matrix_snow_animation(size_t width, size_t height, double spawn_prob, size_t dur_secs, size_t max_amount, std::ostream &os = std::cout);

    void clrprint(const char *tree, std::ostream &os = std::cout);
    void clrprintln(const char *tree, std::ostream &os = std::cout);

    void delprint(const char *line, size_t delay_ms, std::ostream &os = std::cout);
    void delprintln(const char *line, size_t delay_ms, std::ostream &os = std::cout);

    void setup_terminal();
    void clear_terminal();

    const char *heart(size_t size);
}

#endif