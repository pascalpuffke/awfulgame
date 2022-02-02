#pragma once

#include "BaseEntity.h"

namespace Entity {

class AnimatedEntity : public BaseEntity {
public:
    AnimatedEntity(State& state, const std::unordered_map<Direction, std::vector<std::string>>& frames, float animationSpeed, Direction facing);

    ~AnimatedEntity();

    void update(const float deltaTime);

    virtual std::optional<std::shared_ptr<Texture2D>> texture() const override;
    virtual std::string_view textureKey() const override;

protected:
    float m_animationTimer = 0.0f;
    uint32_t m_currentFrame = 0;

    const float m_animationSpeed;
    std::unordered_map<Direction, std::vector<std::string>> m_frames;
};

} // namespace Entity
