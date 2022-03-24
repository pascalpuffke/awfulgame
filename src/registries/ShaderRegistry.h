#pragma once

#include "Registry.h"
#include <raylib-cpp.hpp>

namespace Registries {

class ShaderRegistry final : public Registry<Shader> {
public:
    ShaderRegistry()
            : Registry("ShaderRegistry")
    {
    }

    ~ShaderRegistry() override
    {
        for (auto &[_, shader]: m_registry) {
            UnloadShader(*shader);
        }
    }

    void loadFile(const std::string &key, const char *vsPath, const char *fsPath)
    {
        load(key, LoadShader(vsPath, fsPath));
    }
};

} // namespace Registries
