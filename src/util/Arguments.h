#pragma once

#include <cxxopts.hpp>
#include <fmt/color.h>

namespace Arguments {

struct Configuration {
    bool vsync {};
    bool debug {};
    int32_t fps {};
    std::string resourcePath {}; // TODO
};

Configuration parseArguments(int argc, char **argv)
{
    auto options = cxxopts::Options("game", "A simple 2D game, written in C++20 using the raylib library");
    options.add_options()
        ("h,help", "Print help")
        ("r,res", "Set resource folder", cxxopts::value<std::string>()->default_value("../res"))
        ("f,fps", "Max FPS", cxxopts::value<int32_t>()->default_value(std::to_string(std::numeric_limits<int>::max())))
        ("d,debug", "Start in debugging mode", cxxopts::value<bool>()->default_value("false"))
        ("v,vsync", "Enable vertical synchronization", cxxopts::value<bool>()->default_value("false"));
    options.allow_unrecognised_options();

    auto result = options.parse(argc, argv);

    for (auto &arg : result.unmatched()) {
        fmt::print(fg(fmt::color::yellow), "WARN: Unrecognised argument '{}'\n", arg);
    }

    if (result.count("help")) {
        fmt::print("{}\n", options.help());
        exit(0);
    }

    return Configuration {
        .vsync = result["vsync"].as<bool>(),
        .debug = result["debug"].as<bool>(),
        .fps = result["fps"].as<int32_t>(),
        .resourcePath = result["res"].as<std::string>()
    };
}

} // namespace Arguments
