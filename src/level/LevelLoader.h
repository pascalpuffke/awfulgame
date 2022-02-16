#pragma once

#include "../util/State.h"
#include <filesystem>

namespace Level {

class LevelLoader final {
public:
    explicit LevelLoader(State &state);

    void load(const std::filesystem::path &path);
    void save(const std::filesystem::path &path);

private:
    State &m_state;
};

} // namespace Level
