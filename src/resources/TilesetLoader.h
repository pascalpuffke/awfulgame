#pragma once

#include <cstdint>
#include <filesystem>
#include <raylib-cpp.hpp>
#include <string_view>

namespace Resources {

class TilesetLoader final {
public:
    explicit TilesetLoader(uint32_t tileSize);

    ~TilesetLoader();

    void load(const std::filesystem::path &path);

    [[nodiscard]] Texture2D get(uint32_t offsetX, uint32_t offsetY) const;

private:
    const uint32_t m_tileWidth = 16;
    uint32_t m_tilesetWidth = 0;
    uint32_t m_tilesetHeight = 0;

    Image m_tileset {};
};

} // namespace Resources