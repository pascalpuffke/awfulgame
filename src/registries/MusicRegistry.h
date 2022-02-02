#pragma once

#include "Registry.h"
#include <raylib-cpp.hpp>

namespace Registries {

class MusicRegistry final : public Registry<Music> {
public:
    MusicRegistry()
        : Registry("MusicRegistry")
    {
    }

    virtual ~MusicRegistry() override
    {
        for (auto& [_, music] : m_registry) {
            UnloadMusicStream(*music);
        }
    }

    void loadFile(const std::string& key, const std::string& path)
    {
        load(key, LoadMusicStream(path.c_str()));
    }

    void loadFiles(const std::unordered_map<std::string, std::string>& files)
    {
        for (const auto& [key, path] : files) {
            loadFile(key, path);
        }
    }
};

} // namespace Registries
