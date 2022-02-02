#include "TilesetLoader.h"

#include <fmt/color.h>
#include <fmt/format.h>

namespace Resources {

TilesetLoader::TilesetLoader(const uint32_t tileSize)
    : m_tileWidth(tileSize)
{
}

TilesetLoader::~TilesetLoader()
{
    UnloadImage(m_tileset);
}

void TilesetLoader::load(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path)) {
        fmt::print(fg(fmt::color::red), "[TilesetLoader] Tileset file does not exist: {}\n", std::filesystem::absolute(path).c_str());
        return;
    }
    m_tileset = LoadImage(path.c_str());
    m_tilesetWidth = m_tileset.width / m_tileWidth;
    m_tilesetHeight = m_tileset.height / m_tileWidth;
    fmt::print(fg(fmt::color::light_green), "[TilesetLoader] Loaded tileset {} with {}x{} tiles\n", path.filename().c_str(), m_tileset.width / m_tileWidth, m_tileset.height / m_tileWidth);
}

Texture2D TilesetLoader::get(uint32_t offsetX, uint32_t offsetY) const
{
    const auto tilesetX = (offsetX % m_tilesetWidth) * m_tileWidth;
    const auto tilesetY = (offsetY % m_tilesetHeight) * m_tileWidth;
    const auto tilesetRect = Rectangle { static_cast<float>(tilesetX), static_cast<float>(tilesetY), static_cast<float>(m_tileWidth), static_cast<float>(m_tileWidth) };
    const auto imageCopy = ImageFromImage(m_tileset, tilesetRect);
    const auto texture = LoadTextureFromImage(imageCopy);
    UnloadImage(imageCopy);
    return texture;
}

} // namespace Resources
