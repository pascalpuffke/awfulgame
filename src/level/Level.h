#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Level {

class Level final {
public:
    Level();
    Level(std::string_view name, const uint32_t width, const uint32_t height);

    const std::string& tileAt(const uint32_t x, const uint32_t y, const uint32_t layer) const noexcept;
    const std::string& tileAt(const uint32_t x, const uint32_t y) const noexcept;
    std::string_view name() const;
    uint32_t width() const;
    uint32_t height() const;

    void setTile(const uint32_t x, const uint32_t y, const uint32_t layer, std::string_view tile);
    void setName(std::string_view name);
    void setWidth(const uint32_t width);
    void setHeight(const uint32_t height);

private:
    std::string_view m_name = "map";
    uint32_t m_width = 16;
    uint32_t m_height = 12;

    std::vector<std::vector<std::string>> m_tiles;
};

} // namespace Level
