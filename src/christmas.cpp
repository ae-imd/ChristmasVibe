#include "../include/christmas.h"
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

namespace IMD
{
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
    std::uniform_int_distribution<> dist(0, std::size(COLORS) - 1);
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

void IMD::clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void IMD::delprint(const char *line, size_t delay_ms, std::ostream &os)
{
    if (line == NULL || line[0] == '\0')
        return;

    for (size_t i(0); line[i] != '\0'; ++i)
    {
        os << line[i];
        os.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}
void IMD::delprintln(const char *line, size_t delay_ms, std::ostream &os)
{
    delprint(line, delay_ms, os);
    os << std::endl;
}

void IMD::snow_animation(size_t width, size_t height, double spawn_prob, size_t dur_secs, size_t max_amount, std::ostream &os)
{
    constexpr char SNOW_SYMBOLS[] = {'.', '*', '+'};
    struct snowflake
    {
        size_t x, y;
        int speed;
        char symbol;
        const char *color;
    };

    std::uniform_int_distribution<> col_dist(0, width - 1);
    std::uniform_int_distribution<> speed_dist(1, 2);
    std::uniform_real_distribution<> prob_dist(0.0, 1.0);
    std::uniform_int_distribution<> symbol_dist(0, std::size(SNOW_SYMBOLS) - 1);

    std::vector<snowflake> space;

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(dur_secs);

    while (std::chrono::steady_clock::now() < end_time)
    {
        os << "\033[2J\033[1;1H";

        size_t amount(width * spawn_prob);
        while (amount != 0 && space.size() < max_amount)
        {
            size_t col = col_dist(gen);
            if (prob_dist(gen) < spawn_prob)
            {
                bool top_occupied = false;
                for (const auto &sf : space)
                {
                    if (sf.x == col && sf.y == 0)
                    {
                        top_occupied = true;
                        break;
                    }
                }

                if (!top_occupied)
                {
                    snowflake sf;
                    sf.x = col;
                    sf.y = 0;
                    sf.speed = speed_dist(gen);
                    sf.symbol = SNOW_SYMBOLS[symbol_dist(gen)];
                    sf.color = get_random_color().second;
                    space.push_back(sf);
                }
            }
            --amount;
        }

        for (auto it = space.begin(); it != space.end();)
        {
            os << "\033[" << it->y << ";" << it->x << "H";
            os << " ";

            it->y += it->speed;
            if (it->y > height)
                it = space.erase(it);
            else
            {
                os << "\033[" << it->y << ";" << it->x << "H";
                os << it->color << it->symbol << RESET;
                ++it;
            }
        }
        os << "\033[" << height + 1 << ";1H";
        for (size_t i(0); i < width; ++i)
            os << "-";

        os.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
