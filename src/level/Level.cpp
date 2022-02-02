#include "Level.h"

#include <fmt/color.h>
#include <fmt/format.h>
#include <raylib-cpp.hpp>

namespace Level {

Level::Level() = default;

Level::Level(std::string_view name, const uint32_t width, const uint32_t height)
    : m_name(name)
    , m_width(width)
    , m_height(height)
{
    m_tiles.resize(2);
    for (auto& row : m_tiles)
        row.resize(m_width * m_height);
    std::fill(m_tiles.at(0).begin(), m_tiles.at(0).end(), "grass-0");
    std::fill(m_tiles.at(1).begin(), m_tiles.at(1).end(), "");
}

const std::string& Level::tileAt(const uint32_t x, const uint32_t y, const uint32_t layer) const noexcept
{
    try {
        return m_tiles.at(layer).at(y * m_width + x);
    } catch (std::out_of_range&) {
        fmt::print(fg(fmt::color::yellow), "[Level] WARN: Out of bounds tile access ({}, {}) layer {}\n", x, y, layer);
        return m_tiles.front().at(0);
    }
}

const std::string& Level::tileAt(const uint32_t x, const uint32_t y) const noexcept
{
    if (m_tiles.at(1).at(y * m_width + x).empty())
        return tileAt(x, y, 0);
    return m_tiles.at(1).at(y * m_width + x);
}

std::string_view Level::name() const
{
    return m_name;
}

uint32_t Level::width() const
{
    return m_width;
}

uint32_t Level::height() const
{
    return m_height;
}

void Level::setTile(const uint32_t x, const uint32_t y, const uint32_t layer, std::string_view tile)
{
    m_tiles.at(layer).at(y * m_width + x) = tile;
}

void Level::setName(std::string_view name)
{
    m_name = name;
    SetWindowTitle(m_name.data());
}

void Level::setWidth(const uint32_t width)
{
    m_width = width;
    m_tiles.resize(2);
    for (auto& row : m_tiles)
        row.resize(m_width * m_height);
    std::fill(m_tiles.at(0).begin(), m_tiles.at(0).end(), "grass-0");
    std::fill(m_tiles.at(1).begin(), m_tiles.at(1).end(), "");
}

void Level::setHeight(const uint32_t height)
{
    m_height = height;
    m_tiles.resize(2);
    for (auto& row : m_tiles)
        row.resize(m_width * m_height);
    std::fill(m_tiles.at(0).begin(), m_tiles.at(0).end(), "grass-0");
    std::fill(m_tiles.at(1).begin(), m_tiles.at(1).end(), "");
}

} // namespace Level
