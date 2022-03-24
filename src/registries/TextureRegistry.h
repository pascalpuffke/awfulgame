#pragma once

#include "Registry.h"
#include <raylib-cpp.hpp>

namespace Registries {

class TextureRegistry final : public Registry<Texture2D> {
public:
    TextureRegistry()
            : Registry("TextureRegistry")
    {
    }

    ~TextureRegistry() override
    {
        for (auto &[_, texture]: m_registry) {
            UnloadTexture(*texture);
        }
    }
};

} // namespace Registries