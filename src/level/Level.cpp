#include "Level.h"

#include <fmt/color.h>
#include <raylib-cpp.hpp>
#include <utility>

namespace Level {

Level::Level() = default;

Level::Level(std::string name, uint32_t width, uint32_t height)
    : m_name(std::move(name)), m_width(width), m_height(height)
{
    m_tiles.resize(2);
    for (auto &row : m_tiles)
        row.resize(m_width * m_height);
    std::fill(m_tiles.at(0).begin(), m_tiles.at(0).end(), "grass-0");
    std::fill(m_tiles.at(1).begin(), m_tiles.at(1).end(), "");
}

const std::string &Level::tileAt(uint32_t x, uint32_t y, uint32_t layer) const noexcept
{
    try {
        return m_tiles.at(layer).at(y * m_width + x);
    } catch (std::out_of_range &) {
        fmt::print(fg(fmt::color::yellow), "[Level] WARN: Out of bounds tile access ({}, {}) layer {}\n", x, y, layer);
        return m_tiles.front().at(0);
    }
}

const std::string &Level::tileAt(IntPoint position) const noexcept
{
    if (m_tiles.at(1).at(position.y * m_width + position.x).empty())
        return tileAt(position.x, position.y, 0);
    return m_tiles.at(1).at(position.y * m_width + position.x);
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

IntPoint Level::size() const
{
    return IntPoint {
        static_cast<int32_t>(m_width),
        static_cast<int32_t>(m_height)
    };
}

void Level::setTile(IntPoint position, uint32_t layer, std::string_view tile)
{
    m_tiles.at(layer).at(position.y * m_width + position.x) = tile;
}

void Level::setName(std::string_view name)
{
    m_name = name;
    SetWindowTitle(m_name.data());
}

void Level::setWidth(uint32_t width)
{
    m_width = width;
    m_tiles.resize(2);
    for (auto &row : m_tiles)
        row.resize(m_width * m_height);
    std::fill(m_tiles.at(0).begin(), m_tiles.at(0).end(), "grass-0");
    std::fill(m_tiles.at(1).begin(), m_tiles.at(1).end(), "");
}

void Level::setHeight(uint32_t height)
{
    m_height = height;
    m_tiles.resize(2);
    for (auto &row : m_tiles)
        row.resize(m_width * m_height);
    std::fill(m_tiles.at(0).begin(), m_tiles.at(0).end(), "grass-0");
    std::fill(m_tiles.at(1).begin(), m_tiles.at(1).end(), "");
}

void Level::setSize(IntPoint size)
{
    setWidth(size.x);
    setHeight(size.y);
}

} // namespace Level
