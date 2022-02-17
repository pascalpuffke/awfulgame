#pragma once

#include "Forward.h"

struct State {
    Level::Level &level;
    Registries::TextureRegistry &textures;
    Registries::CommandRegistry &commands;
    Registries::SoundRegistry &sounds;
    Registries::MusicRegistry &music;
    Registries::ShaderRegistry &shaders;
};
