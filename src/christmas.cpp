#include "../include/christmas.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace IMD
{
    std::uniform_int_distribution<> dist(0, std::size(COLORS) - 1);
    std::random_device rd;
    std::mt19937 gen(rd());
}

const char *IMD::christmas_tree(size_t height)
{
    size_t width(2 * height - 1);
    const size_t amount(height * height + (height - 1) + 1);
    char *res = new char[amount];
    size_t ind(0);

    for (size_t lev(0); lev < height; ++lev)
    {
        size_t stars_amount(2 * lev + 1);
        size_t spaces_amount((width - stars_amount) / 2);

        for (size_t i(0); i < spaces_amount; ++i)
            res[ind++] = ' ';
        for (size_t i(0); i < stars_amount; ++i)
            res[ind++] = '*';

        if (lev < height - 1)
            res[ind++] = '\n';
    }
    res[ind] = '\0';
    return res;
}

std::pair<const char *, const char *> IMD::get_random_color()
{
    return COLORS[dist(gen)];
}

void IMD::print_color_tree(const char *tree, std::ostream &os)
{
    if (tree == nullptr || tree[0] == '\0')
        return;

    for (size_t i(0); tree[i] != '\0'; ++i)
    {
        if (tree[i] == '*')
            os << get_random_color().second << "*" << RESET;
        else
            os << tree[i];
    }
}
void IMD::println_color_tree(const char *tree, std::ostream &os)
{
    print_color_tree(tree, os);
    os << std::endl;
}

void IMD::enable_color()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}