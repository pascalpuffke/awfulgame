#pragma once

namespace Level {
class Level;
}

namespace Registries {
class TextureRegistry;
class CommandRegistry;
class SoundRegistry;
class MusicRegistry;
}

struct State {
    Level::Level& level;
    Registries::TextureRegistry& textures;
    Registries::CommandRegistry& commands;
    Registries::SoundRegistry& sounds;
    Registries::MusicRegistry& music;
};
