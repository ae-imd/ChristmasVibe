#include "../include/christmas.h"

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