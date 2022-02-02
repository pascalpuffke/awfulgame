#include "BaseEntity.h"
#include "../level/Level.h"
#include "../registries/SoundRegistry.h"
#include "../registries/TextureRegistry.h"

namespace Entity {

BaseEntity::BaseEntity(State& state, const std::unordered_map<Direction, std::string>& textures, Direction facing = Direction::NORTH)
    : m_state(state)
    , m_textures(textures)
    , m_facing(facing)
{
}

BaseEntity::~BaseEntity() = default;

void BaseEntity::move(Direction direction)
{
    m_facing = direction;

    switch (direction) {
    case Direction::NORTH: {
        auto moveTo = raylib::Vector2 {
            m_position.x,
            m_position.y - SCALED_TEXTURE_RES,
        };
        if (inBounds(moveTo))
            m_position = moveTo;
        else
            PlaySound(*m_state.sounds.get("bonk").value());
        break;
    }
    case Direction::EAST: {
        auto moveTo = raylib::Vector2 {
            m_position.x + SCALED_TEXTURE_RES,
            m_position.y,
        };
        if (inBounds(moveTo))
            m_position = moveTo;
        else
            PlaySound(*m_state.sounds.get("bonk").value());
        break;
    }
    case Direction::SOUTH: {
        auto moveTo = raylib::Vector2 {
            m_position.x,
            m_position.y + SCALED_TEXTURE_RES,
        };
        if (inBounds(moveTo))
            m_position = moveTo;
        else
            PlaySound(*m_state.sounds.get("bonk").value());
        break;
    }
    case Direction::WEST: {
        auto moveTo = raylib::Vector2 {
            m_position.x - SCALED_TEXTURE_RES,
            m_position.y,
        };
        if (inBounds(moveTo))
            m_position = moveTo;
        else
            PlaySound(*m_state.sounds.get("bonk").value());
        break;
    }
    }
}

raylib::Vector2 BaseEntity::position() const
{
    return m_position;
}

std::optional<std::shared_ptr<Texture2D>> BaseEntity::texture() const
{
    return m_state.textures.get(m_textures.at(m_facing));
}

std::string_view BaseEntity::textureKey() const
{
    return m_textures.at(m_facing);
}

Direction BaseEntity::facing() const
{
    return m_facing;
}

constexpr bool BaseEntity::inBounds(const raylib::Vector2& position)
{
    return position.x >= 0 && position.x < m_state.level.width() * SCALED_TEXTURE_RES && position.y >= 0 && position.y < m_state.level.height() * SCALED_TEXTURE_RES;
}

} // namespace Entity
