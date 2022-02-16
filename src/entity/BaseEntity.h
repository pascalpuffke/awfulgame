#pragma once

#include "../util/Constants.h"
#include "../util/Direction.h"
#include "../util/State.h"
#include <memory>
#include <optional>
#include <raylib-cpp.hpp>
#include <string>
#include <robin_hood.h>

namespace Entity {

class BaseEntity {
public:
    BaseEntity(State &state,
               robin_hood::unordered_map<Direction, std::string> &&textures,
               Direction facing,
               float animationSpeed);

    virtual ~BaseEntity();

    virtual void move(Direction direction);

    virtual void update(float deltaTime);

    [[nodiscard]] virtual std::optional<std::shared_ptr<Texture2D>> texture() const;

    [[maybe_unused]] [[nodiscard]] virtual std::string_view textureKey() const;

    [[nodiscard]] raylib::Vector2 position() const;

    [[nodiscard]] Direction facing() const;

protected:
    [[nodiscard]] constexpr bool inBounds(const raylib::Vector2 &position) const;

    const float m_animationSpeed;
    float m_animationTimer = 0.0f;
    uint32_t m_currentFrame = 0;

    raylib::Vector2 m_position = { 8.0f * SCALED_TEXTURE_RES, 6.0f * SCALED_TEXTURE_RES };
    State &m_state;
    Direction m_facing;

    const robin_hood::unordered_map<Direction, std::string> m_textures;
};

} // namespace Entity
