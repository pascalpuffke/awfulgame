#pragma once

#include <string>
#include <vector>
#include "../util/Point.h"

namespace Level {

class Level final {
public:
    Level();
    Level(std::string name, uint32_t width, uint32_t height);

    [[nodiscard]] const std::string &tileAt(uint32_t x, uint32_t y, uint32_t layer) const noexcept;
    [[nodiscard]] const std::string &tileAt(IntPoint position) const noexcept;
    [[nodiscard]] std::string_view name() const;
    [[nodiscard]] uint32_t width() const;
    [[nodiscard]] uint32_t height() const;
    [[nodiscard]] IntPoint size() const;

    void setTile(IntPoint position, uint32_t layer, std::string_view tile);
    void setName(std::string_view name);
    void setWidth(uint32_t width);
    void setHeight(uint32_t height);
    void setSize(IntPoint size);

private:
    std::string m_name = "map";
    uint32_t m_width = 16;
    uint32_t m_height = 12;

    std::vector<std::vector<std::string>> m_tiles;
};

} // namespace Level
