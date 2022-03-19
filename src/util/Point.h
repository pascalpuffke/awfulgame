#pragma once

template<typename T>
struct Point {
    T x;
    T y;

    Point() = default;

    Point(T x, T y) : x(x), y(y) {}

    Point(const Point &) = default;
    Point(Point &&) noexcept = default;
    Point &operator=(const Point &) = default;
    Point &operator=(Point &&) noexcept = default;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const {
        return *this != other;
    }

    Point operator+(const Point &other) const {
        return { x + other.x, y + other.y };
    }

    Point operator-(const Point &other) const {
        return { x - other.x, y - other.y };
    }

    Point operator*(T scalar) const {
        return { x * scalar, y * scalar };
    }

    Point operator/(T scalar) const {
        return { x / scalar, y / scalar };
    }

    Point &operator+=(const Point &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point &operator-=(const Point &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Point &operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Point &operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    [[nodiscard]] constexpr bool inBounds(Point size, bool positive = true) const {
        if (positive)
            return x >= 0 && y >= 0 && x < size.x && y < size.y;
        return x < size.x && y < size.y;
    }
};

/// @brief A point in 2D space with signed 32-bit integer coordinates.
using IntPoint = Point<int>;
