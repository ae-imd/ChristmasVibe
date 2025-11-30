#include "../include/christmas.h"
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <cmath>
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
    std::uniform_int_distribution<> dist(1, std::size(COLORS) - 1);
    return COLORS[dist(gen)];
}

void IMD::clrprint(const char *tree, std::ostream &os)
{
    if (tree == nullptr || tree[0] == '\0')
        return;

    for (size_t i(0); tree[i] != '\0'; ++i)
    {
        if (tree[i] == '*')
            os << get_random_color().second << "*" << COLORS[0].second;
        else
            os << tree[i];
    }
}
void IMD::clrprintln(const char *tree, std::ostream &os)
{
    clrprint(tree, os);
    os << std::endl;
}

void IMD::setup_terminal()
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

void IMD::clear_terminal()
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

void IMD::struct_snow_animation(size_t width, size_t height, double spawn_prob, size_t dur_secs, size_t max_amount, std::ostream &os)
{
    constexpr char SNOW_SYMBOLS[] = {'.', '*', '+'};
    struct snowflake
    {
        size_t x, y;
        char symbol;
        const char *color;
    };

    std::uniform_int_distribution<> col_dist(0, width - 1);
    std::uniform_real_distribution<> prob_dist(0.0, 1.0);
    std::uniform_int_distribution<> symbol_dist(0, std::size(SNOW_SYMBOLS) - 1);

    std::vector<snowflake> space;

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(dur_secs);

    while (std::chrono::steady_clock::now() < end_time)
    {
        os << CLEAR;

        size_t field(width * spawn_prob);
        while (field != 0 && space.size() < max_amount)
        {
            size_t col = col_dist(gen);
            if (prob_dist(gen) < spawn_prob)
            {
                bool flag(false);
                for (const auto &sf : space)
                {
                    if (sf.x == col && sf.y == 0)
                    {
                        flag = true;
                        break;
                    }
                }

                if (!flag)
                {
                    snowflake sf;
                    sf.x = col;
                    sf.y = 0;
                    sf.symbol = SNOW_SYMBOLS[symbol_dist(gen)];
                    sf.color = get_random_color().second;
                    space.push_back(sf);
                }
            }
            --field;
        }

        for (auto it = space.begin(); it != space.end();)
        {
            os << "\033[" << it->y << ";" << it->x << "H";
            os << " ";

            it->y += 1;
            if (it->y > height)
                it = space.erase(it);
            else
            {
                os << "\033[" << it->y << ";" << it->x << "H";
                os << it->color << it->symbol << COLORS[0].second;
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
void IMD::matrix_snow_animation(size_t width, size_t height, double spawn_prob, size_t dur_secs, size_t max_amount, std::ostream &os)
{
    constexpr char SNOW_SYMBOLS[] = {'.', '*', '+'};
    using cell = std::pair<char, const char *>;

    cell **mrx = new cell *[height];
    for (size_t i(0); i < height; ++i)
    {
        mrx[i] = new cell[width];
        for (size_t j(0); j < width; ++j)
            mrx[i][j] = {' ', ""};
    }

    std::uniform_int_distribution<> col_dist(0, width - 1);
    std::uniform_real_distribution<> prob_dist(0.0, 1.0);
    std::uniform_int_distribution<> symbol_dist(0, std::size(SNOW_SYMBOLS) - 1);

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(dur_secs);
    size_t amount(0);

    while (std::chrono::steady_clock::now() < end_time)
    {
        os << CLEAR;

        size_t field(width * spawn_prob);
        while (field != 0 && amount < max_amount)
        {
            size_t col = col_dist(gen);
            if (prob_dist(gen) < spawn_prob)
            {
                if (mrx[0][col].first == ' ')
                {
                    mrx[0][col].first = SNOW_SYMBOLS[symbol_dist(gen)];
                    mrx[0][col].second = get_random_color().second;
                    ++amount;
                }
            }
            --field;
        }

        for (int y(height - 1); y >= 0; --y)
        {
            for (size_t x(0); x < width; ++x)
            {
                if (mrx[y][x].first != ' ')
                {
                    if (y + 1 < height && mrx[y + 1][x].first == ' ')
                    {
                        mrx[y + 1][x] = mrx[y][x];
                        mrx[y][x] = {' ', ""};
                    }
                    else if (y + 1 >= height)
                        mrx[y][x] = {' ', ""};
                }
            }
        }

        for (size_t y(0); y < height; ++y)
        {
            for (size_t x(0); x < width; ++x)
            {
                if (mrx[y][x].first != ' ')
                    os << mrx[y][x].second << mrx[y][x].first << COLORS[0].second;
                else
                    os << ' ';
            }
            os << std::endl;
        }

        os << std::endl;
        for (size_t i(0); i < width + 2; ++i)
            os << '-';

        os.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (size_t i(0); i < height; ++i)
        delete[] mrx[i];
    delete[] mrx;

    os << CLEAR;
}

const char *IMD::heart(size_t size)
{
    if (size <= 1)
        return NULL;

    std::stringstream ss;
    double tmp = static_cast<double>(size);

    for (double x(0); x < tmp; ++x)
    {
        for (double y(0); y <= 4 * tmp; ++y)
        {
            double dist1 = sqrt(pow(x - tmp, 2) + pow(y - tmp, 2));
            double dist2 = sqrt(pow(x - tmp, 2) + pow(y - 3 * tmp, 2));

            if (dist1 < tmp + 0.5 || dist2 < tmp + 0.5)
                ss << "*";
            else
                ss << " ";
        }
        ss << std::endl;
    }

    // Нижняя часть сердца (треугольник)
    for (double x(1); x < 2 * tmp; ++x)
    {
        for (double y(0); y < x; ++y)
            ss << " ";

        for (double y(0); y < 4 * tmp + 1 - 2 * x; ++y)
            ss << "*";

        ss << std::endl;
    }

    std::string result_str = ss.str();
    char *result = new char[result_str.length() + 1];
    strcpy(result, result_str.c_str());

    return result;
}
