#include "AnimatedEntity.h"
#include "../registries/TextureRegistry.h"

#include <fmt/color.h>
#include <fmt/format.h>

namespace Entity {

AnimatedEntity::AnimatedEntity(State &state, robin_hood::unordered_map<Direction, std::vector<std::string>> &&frames,
                               float animationSpeed, Direction facing = Direction::NORTH)
    : BaseEntity(state, {
    { Direction::NORTH, frames.at(Direction::NORTH).at(0) },
    { Direction::EAST, frames.at(Direction::EAST).at(0) },
    { Direction::SOUTH, frames.at(Direction::SOUTH).at(0) },
    { Direction::WEST, frames.at(Direction::WEST).at(0) },
}, facing, animationSpeed), m_frames(std::move(frames))
{
    fmt::print(fg(fmt::color::light_green), "[AnimatedEntity] Created with {} frames\n",
               m_frames.at(m_facing).size());
}

void AnimatedEntity::update(float deltaTime)
{
    m_animationTimer += deltaTime;
    if (m_animationTimer >= m_animationSpeed) {
        m_animationTimer = 0.0f;
        m_currentFrame++;
        if (m_currentFrame >= m_frames.at(m_facing).size())
            m_currentFrame = 0;
    }
}

std::optional<std::shared_ptr<Texture2D>> AnimatedEntity::texture() const
{
    return m_state.textures.get(m_frames.at(m_facing).at(m_currentFrame));
}

std::string_view AnimatedEntity::textureKey() const
{
    return m_frames.at(m_facing).at(m_currentFrame);
}

} // namespace Entity
