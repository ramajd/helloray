#pragma once

#include <vec3.h>

#include <iostream>

using color = vec3;

void write_color(std::ostream &out, const color &pixel)
{
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << std::endl;
}