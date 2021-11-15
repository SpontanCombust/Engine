#ifndef __COLOR_H__
#define __COLOR_H__

#include <string>

struct ColorRGB
{
    unsigned char r, g, b;

    std::string to_string() const;
};

#endif // __COLOR_H__