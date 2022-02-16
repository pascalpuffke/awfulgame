#pragma once

#include <cstdint>

/// @brief A point in 2D space with signed 32-bit integer coordinates.
struct IntPoint {
    int32_t x;
    int32_t y;

    [[nodiscard]] constexpr bool inBounds(IntPoint size, bool positive = true) const
    {
        if (positive)
            return x >= 0 && y >= 0 && x < size.x && y < size.y;
        return x < size.x && y < size.y;
    }
};
