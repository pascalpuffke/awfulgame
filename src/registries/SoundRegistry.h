#pragma once

#include "Registry.h"
#include <raylib-cpp.hpp>

namespace Registries {

class SoundRegistry final : public Registry<Sound> {
public:
    SoundRegistry()
        : Registry("SoundRegistry")
    {
    }

    ~SoundRegistry() override
    {
        for (auto&[_, sound] : m_registry) {
            UnloadSound(*sound);
        }
    }

    void loadFile(const std::string &key, const std::string &path)
    {
        load(key, LoadSound(path.c_str()));
    }

    void loadFiles(const robin_hood::unordered_map<std::string, std::string> &files)
    {
        for (const auto&[key, path] : files) {
            loadFile(key, path);
        }
    }
};

} // namespace Registries
