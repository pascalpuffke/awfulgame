#include "LevelLoader.h"

#include <fmt/color.h>
#include <fmt/format.h>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "../registries/CommandRegistry.h"

namespace Level {

LevelLoader::LevelLoader(State& state)
    : m_state(state)
{
}

void LevelLoader::load(const std::filesystem::path& file)
{
    const auto absolutePath = file.is_absolute() ? file : std::filesystem::absolute(file);
    fmt::print("[LevelLoader] Loading level from {}...\n", absolutePath.string());
    if (!std::filesystem::exists(file)) {
        fmt::print(fg(fmt::color::red), "[LevelLoader] ERROR: File {} does not exist\n", absolutePath.string());
    }

    std::ifstream stream(file);
    std::string line;
    std::vector<std::string> params;

    auto split = [](const std::string& str, char delim) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delim)) {
            if (!token.empty())
                tokens.push_back(token);
        }
        return tokens;
    };

    while (std::getline(stream, line)) {
        if (line.empty() || line.starts_with("#"))
            continue;

        params = split(line, ' ');
        if (params.size() == 0)
            continue;

        auto command = m_state.commands.get(params[0]);
        if (!command.has_value())
            continue;

        (*command.value())(m_state, std::vector<std::string_view>(params.begin() + 1, params.end()));
    }

    stream.close();
}

void LevelLoader::save(const std::filesystem::path& file)
{
}

} // namespace Level
