#include "Color.hpp"

std::string ColorRGB::to_string() const
{
    std::string s;
    s += "[";
    s += std::to_string(r) + ", ";
    s += std::to_string(g) + ", ";
    s += std::to_string(b) + "]";

    return s;
}
