#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "../include/christmas.h"

int main()
{
    IMD::enable_color();
    IMD::matrix_snow_animation(80, 24, 0.3, 20, 1000);

    return 0;
}