#pragma once

#include "BaseEntity.h"

namespace Entity {

class AnimatedEntity : public BaseEntity {
public:
    AnimatedEntity(State &state, robin_hood::unordered_map<Direction, std::vector<std::string>> &&frames,
                   float animationSpeed, Direction facing);

    void update(float deltaTime) override;

    [[nodiscard]] std::optional<std::shared_ptr<Texture2D>> texture() const override;

    [[nodiscard]] std::string_view textureKey() const override;

protected:
    robin_hood::unordered_map<Direction, std::vector<std::string>> m_frames;
};

} // namespace Entity
