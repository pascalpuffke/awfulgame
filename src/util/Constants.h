#pragma once

#include <limits>

constexpr auto VSYNC_ENABLED = false;
constexpr auto FPS = std::numeric_limits<int>::max();
constexpr auto TEXTURE_RES = 16;
constexpr auto SCALE = 5.0f;
constexpr auto SCALED_TEXTURE_RES = TEXTURE_RES * SCALE;
constexpr auto WIDTH = SCALE * TEXTURE_RES * 16;
constexpr auto HEIGHT = SCALE * TEXTURE_RES * 12;
