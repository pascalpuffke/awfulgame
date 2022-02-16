#pragma once

#include "AnimatedEntity.h"

namespace Entity {

class PlayerEntity final : public AnimatedEntity {
public:
    PlayerEntity(State &state, robin_hood::unordered_map<Direction, std::vector<std::string>> &&frames);

private:
    static constexpr uint32_t m_movementSpeed = 100;
    uint32_t m_movementTimer = 0;
};

} // namespace Entity
