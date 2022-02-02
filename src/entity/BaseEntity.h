#pragma once

#include "../util/Constants.h"
#include "../util/Direction.h"
#include "../util/State.h"
#include <memory>
#include <optional>
#include <raylib-cpp.hpp>
#include <string>
#include <unordered_map>

namespace Entity {

class BaseEntity {
public:
    BaseEntity(State& state, const std::unordered_map<Direction, std::string>& textures, Direction facing);

    virtual ~BaseEntity();

    virtual void move(Direction direction);

    virtual std::optional<std::shared_ptr<Texture2D>> texture() const;
    virtual std::string_view textureKey() const;
    raylib::Vector2 position() const;
    Direction facing() const;

protected:
    constexpr bool inBounds(const raylib::Vector2& position);

    raylib::Vector2 m_position = { 8.0f * SCALED_TEXTURE_RES, 6.0f * SCALED_TEXTURE_RES };
    State& m_state;
    Direction m_facing;

    const std::unordered_map<Direction, std::string> m_textures;
};

} // namespace Entity
