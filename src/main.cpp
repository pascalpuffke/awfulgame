/*
 * Credits for all resources used in this project: "Ninja Adventure" asset pack
 *  - https://pixel-boy.itch.io/ninja-adventure-asset-pack
 *  - Creator: https://www.patreon.com/pixelarchipel
 */

// This is a MASSIVE abomination. Everything sucks.
// You'd probably lose brain cells looking at this.

#include <chrono>
#include <thread>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-const-int-float-conversion"
#endif

#include <raylib-cpp.hpp>

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#include "entity/PlayerEntity.h"
#include "level/Level.h"
#include "level/LevelLoader.h"
#include "registries/CommandRegistry.h"
#include "registries/MusicRegistry.h"
#include "registries/SoundRegistry.h"
#include "registries/TextureRegistry.h"
#include "resources/TilesetLoader.h"
#include "util/Arguments.h"
#include "util/Benchmarking.h"
#include "util/Constants.h"
#include "util/Direction.h"
#include "util/Time.h"

void log(int logLevel, const char *text, va_list args)
{
    auto color = fmt::color::white;

    switch (logLevel) {
    case LOG_INFO:
        color = fmt::color::aquamarine;
        break;
    case LOG_ERROR:
        color = fmt::color::red;
        break;
    case LOG_WARNING:
        color = fmt::color::yellow;
        break;
    case LOG_DEBUG:
        color = fmt::color::light_gray;
        break;
    default:
        break;
    }

    fmt::print(fmt::fg(color), "[{}] ", Time::iso8601());
    vprintf(text, args);
    fmt::print("\n");
}

void loadTextures(Registries::TextureRegistry &textureRegistry)
{
    auto timer = Benchmark::ScopedTimer("loadTextures()");

    // TODO: Use a single TilesetLoader for all tilesets
    auto floorTileset = Resources::TilesetLoader(16);
    floorTileset.load("../res/textures/tile/TilesetFloor.png");
    auto natureTileset = Resources::TilesetLoader(16);
    natureTileset.load("../res/textures/tile/TilesetNature.png");
    auto playerTileset = Resources::TilesetLoader(16);
    playerTileset.load("../res/textures/entity/PlayerSheet.png");

    textureRegistry.loadAll({
                                { "player-east-0", playerTileset.get(3, 0) },
                                { "player-east-1", playerTileset.get(3, 1) },
                                { "player-east-2", playerTileset.get(3, 2) },
                                { "player-east-3", playerTileset.get(3, 3) },
                                { "player-east-4", playerTileset.get(3, 4) },
                                { "player-north-0", playerTileset.get(1, 0) },
                                { "player-north-1", playerTileset.get(1, 1) },
                                { "player-north-2", playerTileset.get(1, 2) },
                                { "player-north-3", playerTileset.get(1, 3) },
                                { "player-north-4", playerTileset.get(1, 4) },
                                { "player-south-0", playerTileset.get(0, 0) },
                                { "player-south-1", playerTileset.get(0, 1) },
                                { "player-south-2", playerTileset.get(0, 2) },
                                { "player-south-3", playerTileset.get(0, 3) },
                                { "player-south-4", playerTileset.get(0, 4) },
                                { "player-west-0", playerTileset.get(2, 0) },
                                { "player-west-1", playerTileset.get(2, 1) },
                                { "player-west-2", playerTileset.get(2, 2) },
                                { "player-west-3", playerTileset.get(2, 3) },
                                { "player-west-4", playerTileset.get(2, 4) },

                                { "grass-top-left", floorTileset.get(0, 7) },
                                { "grass-top-mid", floorTileset.get(1, 7) },
                                { "grass-top-right", floorTileset.get(2, 7) },
                                { "grass-mid-left", floorTileset.get(0, 8) },
                                { "grass-mid-right", floorTileset.get(2, 8) },
                                { "grass-bot-left", floorTileset.get(0, 9) },
                                { "grass-bot-mid", floorTileset.get(1, 9) },
                                { "grass-bot-right", floorTileset.get(2, 9) },

                                { "grass-0", floorTileset.get(0, 12) },
                                { "grass-1", floorTileset.get(1, 12) },
                                { "grass-2", floorTileset.get(2, 12) },
                                { "grass-3", floorTileset.get(3, 12) },
                                { "grass-4", floorTileset.get(4, 12) },

                                { "dirt-0", floorTileset.get(1, 8) },
                                { "dirt-1", floorTileset.get(0, 11) },
                                { "dirt-2", floorTileset.get(1, 11) },

                                { "tree-single-0", natureTileset.get(0, 0) },
                                { "tree-single-1", natureTileset.get(1, 0) },
                                { "tree-single-2", natureTileset.get(0, 1) },
                                { "tree-single-3", natureTileset.get(1, 1) },
                                { "tree-group-0", natureTileset.get(5, 2) },
                                { "tree-group-1", natureTileset.get(6, 2) },
                                { "tree-group-2", natureTileset.get(4, 3) },
                                { "tree-group-3", natureTileset.get(5, 3) },
                                { "tree-group-4", natureTileset.get(6, 3) },
                                { "tree-group-5", natureTileset.get(7, 3) },
                                { "tree-group-6", natureTileset.get(4, 4) },
                                { "tree-group-7", natureTileset.get(5, 4) },
                                { "tree-group-8", natureTileset.get(6, 4) },
                                { "tree-group-9", natureTileset.get(7, 4) },

                                { "flower-0", natureTileset.get(0, 11) },
                            });

    // TODO: implement vignette as shader
    {
        auto vignetteImage = LoadImage("../res/textures/window/vignette.png");
        ImageResize(&vignetteImage, WIDTH, HEIGHT);
        textureRegistry.load("vignette", LoadTextureFromImage(vignetteImage));
        UnloadImage(vignetteImage);
    }
}

void loadCommands(Registries::CommandRegistry &commandRegistry)
{
    auto timer = Benchmark::ScopedTimer("loadCommands()");
    auto set = [&](State &state, IntPoint pos, int layer, const std::string &tile) {
        if (!pos.inBounds(state.level.size()))
            return;
        state.level.setTile(pos, layer, tile);
    };

    // TODO make this less stupid
    auto connectNearbyGrass = [&](State &state, IntPoint pos, int layer) {
        // Dirt tiles that are next to grass tiles should always be connected by special edge tiles.
        set(state, { pos.x - 1, pos.y - 1 }, layer, "grass-top-left");
        set(state, { pos.x, pos.y - 1 }, layer, "grass-top-mid");
        set(state, { pos.x + 1, pos.y - 1 }, layer, "grass-top-right");
        set(state, { pos.x - 1, pos.y }, layer, "grass-mid-left");
        set(state, { pos.x, pos.y }, layer, "dirt-0");
        set(state, { pos.x + 1, pos.y }, layer, "grass-mid-right");
        set(state, { pos.x - 1, pos.y + 1 }, layer, "grass-bot-left");
        set(state, { pos.x, pos.y + 1 }, layer, "grass-bot-mid");
        set(state, { pos.x + 1, pos.y + 1 }, layer, "grass-bot-right");
    };

    auto buildTree = [&](State &state, IntPoint pos, int layer) {
        set(state, { pos.x, pos.y }, layer, "tree-single-0");
        set(state, { pos.x + 1, pos.y }, layer, "tree-single-1");
        set(state, { pos.x, pos.y + 1 }, layer, "tree-single-2");
        set(state, { pos.x + 1, pos.y + 1 }, layer, "tree-single-3");
    };

    commandRegistry.load("name", [&](State &state, const std::vector<std::string_view> &params) {
        // TODO: This does not allow spaces
        if (params.size() != 1) {
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Invalid number of parameters for name command (expected 1, got {})\n",
                       params.size());
            fmt::print(fg(fmt::color::yellow), "[LevelLoader] WARN: Usage: 'name <level_name>'\n");
            return;
        }

        state.level.setName(params[0]);
    });

    commandRegistry.load("size", [&](State &state, const std::vector<std::string_view> &params) {
        if (params.size() != 2) {
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Invalid number of parameters for size command (expected 2, got {})\n",
                       params.size());
            fmt::print(fg(fmt::color::yellow), "[LevelLoader] WARN: Usage: 'size <width> <height>'\n");
            return;
        }

        state.level.setSize({ std::stoi(params[0].data()), std::stoi(params[1].data()) });
    });

    commandRegistry.load("tile", [&](State &state, const std::vector<std::string_view> &params) {
        if (params.size() != 4) {
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Invalid number of parameters for tile command (expected 4, got {})\n",
                       params.size());
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Usage: 'tile <pos_x> <pos_y> <layer_id> <tile_name>'\n");
            return;
        }

        auto pos = IntPoint { std::stoi(params[0].data()), std::stoi(params[1].data()) };
        auto layer = std::stoi(params[2].data());
        auto tile = params[3];

        if (!pos.inBounds(state.level.size())) {
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Out of bounds tile position ({}, {})\n",
                       pos.x,
                       pos.y);
            return;
        }

        if (tile == "dirt") {
            connectNearbyGrass(state, pos, layer);
            return;
        }

        if (tile == "tree") {
            buildTree(state, pos, layer);
            return;
        }

        state.level.setTile(pos, layer, tile);
    });

    commandRegistry.load("fill", [&](State &state, const std::vector<std::string_view> &params) {
        if (params.size() != 6) {
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Invalid number of parameters for fill command (expected 6, got {})\n",
                       params.size());
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Usage: 'fill <from_x> <from_y> <to_x> <to_y> <layer_id> <tile_name>'\n");
            return;
        }

        auto from = IntPoint { std::stoi(params[0].data()), std::stoi(params[1].data()) };
        auto to = IntPoint { std::stoi(params[2].data()), std::stoi(params[3].data()) };
        auto layer = std::stoi(params[4].data());
        auto tile = params[5];

        if (!from.inBounds(state.level.size()) || !to.inBounds(state.level.size())) {
            fmt::print(fg(fmt::color::yellow),
                       "[LevelLoader] WARN: Out of bounds tile position from=({}, {}) to=({}, {})\n",
                       from.x,
                       from.y,
                       to.x,
                       to.y);
            return;
        }

        auto &tileCommand = **commandRegistry.get("tile");
        for (auto x = from.x; x <= to.x; x++) {
            for (auto y = from.y; y <= to.y; y++) {
                tileCommand(state, { std::to_string(x), std::to_string(y), std::to_string(layer), tile });
            }
        }
    });
}

void loadSounds(Registries::SoundRegistry &soundRegistry)
{
    auto timer = Benchmark::ScopedTimer("loadSounds()");
    soundRegistry.loadFile("bonk", "../res/sounds/bonk.wav");
}

void loadMusic(Registries::MusicRegistry &musicRegistry)
{
    auto timer = Benchmark::ScopedTimer("loadMusic()");
    musicRegistry.loadFile("main", "../res/sounds/music.wav");
}

void loadLevel(Level::LevelLoader &loader)
{
    if (std::filesystem::exists("../res/levels/savestate.level")) {
        loader.load("../res/levels/savestate.level");
        fmt::print("[LevelLoader] Loaded saved level file\n");
    } else {
        loader.load("../res/levels/default.level");
        fmt::print("[LevelLoader] Loaded default level file\n");
    }
}

bool checkWorkingDirectory()
{
    auto cwd = std::filesystem::current_path();
    fmt::print("Current working directory: {}\n", cwd.c_str());
    if (std::filesystem::exists("../res"))
        return true;

    fmt::print(fg(fmt::color::red), "ERROR: Could not find '../res' folder.\n");
    return false;
}

int main(int argc, char **argv)
{
    SetTraceLogCallback(log);

    auto config = Arguments::parseArguments(argc, argv);
    auto window = raylib::Window(WIDTH, HEIGHT, "");

    if (!checkWorkingDirectory()) {
        window.SetTargetFPS(1);
        while (!window.ShouldClose()) {
            window.BeginDrawing();
            window.ClearBackground(RAYWHITE);
            DrawText("Please run this program from the build directory of the project.", 20, HEIGHT / 2, 30, BLACK);
            DrawText("(e.g. 'cd <project_root>/build && ./Game')", 20, HEIGHT / 2 + 70, 20, BLACK);
            window.EndDrawing();
        }
        return 1;
    }

    auto level = Level::Level("default", 24, 18);
    auto textureRegistry = Registries::TextureRegistry();
    auto commandRegistry = Registries::CommandRegistry();
    auto soundRegistry = Registries::SoundRegistry();
    auto musicRegistry = Registries::MusicRegistry();

    InitAudioDevice();

    loadTextures(textureRegistry);
    loadCommands(commandRegistry);
    loadSounds(soundRegistry);
    loadMusic(musicRegistry);

    auto state = State {
        .level = level,
        .textures = textureRegistry,
        .commands = commandRegistry,
        .sounds = soundRegistry,
        .music = musicRegistry,
    };
    auto player = Entity::PlayerEntity(state, {
        { Direction::NORTH, { "player-north-0", "player-north-1", "player-north-2", "player-north-3" }},
        { Direction::EAST, { "player-east-0", "player-east-1", "player-east-2", "player-east-3" }},
        { Direction::SOUTH, { "player-south-0", "player-south-1", "player-south-2", "player-south-3" }},
        { Direction::WEST, { "player-west-0", "player-west-1", "player-west-2", "player-west-3" }},
    });
    auto camera = raylib::Camera2D(
        raylib::Vector2(WIDTH / 2, HEIGHT / 2),
        raylib::Vector2(player.position().x + 8, player.position().y + 8),
        0.0f,
        1.0f);

    auto levelLoader = Level::LevelLoader(state);
    loadLevel(levelLoader);

    fmt::print("Level name: {}\n", level.name());
    fmt::print("Level size: {}x{} tiles\n", level.width(), level.height());

    window.SetTargetFPS(config.vsync ? GetMonitorRefreshRate(GetCurrentMonitor()) : config.fps);

    auto frame_time = 0.0f;
    // undef this if it annoys you :)
#define FPS_THREAD
#ifdef FPS_THREAD
    std::thread([&]() {
        while (!window.ShouldClose()) {
            if (frame_time != 0.0f)
                fmt::print("{:.3f}ms/frame {}fps ({:.3f}ms)\n",
                           window.GetFrameTime() * 1000.0f,
                           window.GetFPS(),
                           frame_time);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }).detach();
#endif

    // TODO: The game spends most of its time right here, fetching texture resources hundreds of thousands of times per second.
    //       This is a performance bottleneck and actually makes this more expensive than rendering, at least with unlocked FPS.
    //       We should probably move the texture loading to a separate thread or stop fetching every texture every frame.
    auto getTexture = [&](const std::string &name) {
        try {
            return *(*textureRegistry.get(name));
        }
        catch (std::bad_optional_access &e) {
            fmt::print(fg(fmt::color::yellow), "WARN: Texture '{}' not found\n", name);
            return *(*textureRegistry.get("grass-0"));
        }
    };

    while (!window.ShouldClose()) {
        if (IsKeyPressed(KEY_W))
            player.move(Direction::NORTH);
        if (IsKeyPressed(KEY_S))
            player.move(Direction::SOUTH);
        if (IsKeyPressed(KEY_A))
            player.move(Direction::WEST);
        if (IsKeyPressed(KEY_D))
            player.move(Direction::EAST);

        camera.SetTarget(player.position());

        const auto start = std::chrono::high_resolution_clock::now();
        window.BeginDrawing();
        {
            ClearBackground(BLACK);
            BeginMode2D(camera);
            {
                // TODO: this is scuffed
                for (auto x = 0; x < level.width(); x++) {
                    for (auto y = 0; y < level.height(); y++) {
                        for (auto layer = 0; layer < 2; layer++) {
                            const auto &tile = level.tileAt(x, y, layer);
                            if (tile.empty())
                                continue;

                            DrawTextureEx(*textureRegistry.get(tile).value_or(*textureRegistry.get("grass-0")),
                                          { x * SCALED_TEXTURE_RES, y * SCALED_TEXTURE_RES }, 0.0f, SCALE, WHITE);
                        }
                    }
                }

                DrawTextureEx(**player.texture(), player.position(), 0.0f, SCALE, WHITE);

                const auto mousePos = Vector2Add(GetMousePosition(),
                                                 Vector2Subtract(camera.GetTarget(), camera.GetOffset()));
                const auto tilePos = IntPoint {
                    static_cast<int32_t>(mousePos.x / SCALED_TEXTURE_RES),
                    static_cast<int32_t>(mousePos.y / SCALED_TEXTURE_RES)
                };

                if (tilePos.inBounds(level.size())) {
                    const auto tile = level.tileAt(tilePos).c_str();
                    DrawRectangle(mousePos.x + 16, mousePos.y, MeasureText(tile, 20) + 5, 45, WHITE);
                    DrawText(TextFormat("(%d %d)", tilePos.x, tilePos.y), mousePos.x + 16, mousePos.y, 20, BLACK);
                    DrawText(tile, mousePos.x + 16, mousePos.y + 20, 20, BLACK);
                }
            }
            EndMode2D();

            DrawFPS(10, 10);
            DrawTexture(getTexture("vignette"), 0, 0, WHITE);
        }
        window.EndDrawing();

        frame_time = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count() / 1000.0f;
        player.update(frame_time);
    }

    levelLoader.save("../res/levels/savestate.level");

    return 0;
}
