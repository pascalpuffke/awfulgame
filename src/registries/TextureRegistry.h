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

    virtual ~TextureRegistry() override
    {
        for (auto& [_, texture] : m_registry) {
            UnloadTexture(*texture);
        }
    }

    void loadFile(const std::string& key, const std::string& path)
    {
        load(key, LoadTexture(path.c_str()));
    }

    void loadFiles(const std::unordered_map<std::string, std::string>& files)
    {
        for (const auto& [key, path] : files) {
            loadFile(key, path);
        }
    }
};
} // namespace Registries