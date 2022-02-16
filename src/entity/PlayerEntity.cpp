#include "PlayerEntity.h"

#include <fmt/format.h>

namespace Entity {

PlayerEntity::PlayerEntity(State &state, robin_hood::unordered_map<Direction, std::vector<std::string>> &&frames)
    : AnimatedEntity(state, std::move(frames), 1000 / 3.0f, Direction::EAST)
{
}

} // namespace Entity