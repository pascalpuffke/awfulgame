#pragma once

#include "AnimatedEntity.h"

namespace Entity {

class PlayerEntity final : public AnimatedEntity {
public:
    PlayerEntity(State& state, const std::unordered_map<Direction, std::vector<std::string>>& frames)
        : AnimatedEntity(state, frames, 1000 / 3.0f, Direction::EAST)
    {
    }
};

} // namespace Entity
