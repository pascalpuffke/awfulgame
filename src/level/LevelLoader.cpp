#include "LevelLoader.h"

#include <fmt/color.h>
#include <fstream>
#include <optional>
#include <vector>

#include "../registries/CommandRegistry.h"
#include "../level/Level.h"
#include "../util/Benchmarking.h"

namespace Level {

LevelLoader::LevelLoader(State &state)
    : m_state(state)
{
}

void LevelLoader::load(const std::filesystem::path &file)
{
    const auto _ = Benchmark::ScopedTimer("LevelLoader::load()");

    const auto absolutePath = file.is_absolute() ? file : std::filesystem::absolute(file);
    fmt::print("[LevelLoader] Loading level from {}...\n", absolutePath.string());
    if (!std::filesystem::exists(file)) {
        fmt::print(fg(fmt::color::red), "[LevelLoader] ERROR: File {} does not exist\n", absolutePath.string());
    }

    std::ifstream stream(file);
    std::string line;
    std::vector<std::string> params;

    auto split = [](const std::string &str, char delim) {
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
        if (params.empty())
            continue;

        auto command = m_state.commands.get(params[0]);
        if (!command.has_value())
            continue;

        (*command.value())(m_state, std::vector<std::string_view>(params.begin() + 1, params.end()));
    }

    stream.close();
}

void LevelLoader::save(const std::filesystem::path &file)
{
    const auto _ = Benchmark::ScopedTimer("LevelLoader::save()");

    const auto absolutePath = file.is_absolute() ? file : std::filesystem::absolute(file);
    fmt::print("[LevelLoader] Saving level to {}...\n", absolutePath.string());

#if 0
#include "../util/Time.h"
    std::ofstream stream(file);
    stream << fmt::format("# Save state level file\n# Created: {}\n\n", Time::iso8601());

    stream << fmt::format("name {}\n", m_state.level.name());
    stream << fmt::format("size {} {}\n", m_state.level.width(), m_state.level.height());

    for (auto layer = 0; layer < 2; layer++) {
        for (auto x = 0; x < m_state.level.width(); x++) {
            for (auto y = 0; y < m_state.level.height(); y++) {
                const auto &tile = m_state.level.tileAt(x, y, layer);

                if (tile.empty())
                    continue;

                if (layer == 0 && tile == "grass-0")
                    continue;

                stream << fmt::format("tile {} {} {}\n", tile, x, y);
            }
        }
    }

    stream.close();
#endif
}

} // namespace Level
