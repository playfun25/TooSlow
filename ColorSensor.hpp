#include <stdint.h>

#pragma once

class ColorSensor
{
    public:
        enum class Color
        {
            GREEN = 0,
            RED,
            BLUE,
            NUM_COLORS
        };

    public:
        virtual void powerUp() = 0;
        virtual void powerDown() = 0;
        virtual uint16_t readColor(const Color color) = 0;
};