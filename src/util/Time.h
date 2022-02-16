#pragma once

#include <string>
#include <fmt/chrono.h>

class Time {
public:
    /// @brief Returns the current Unix epoch timestamp in seconds.
    static long currentTime()
    {
        return std::time(nullptr);
    }

    /// @brief Returns the current time as a string in the ISO 8601-standard format "YYYY-mm-ddTHH:MM:SSz"
    static std::string iso8601()
    {
        return fmt::format("{:%Y-%m-%dT%H:%M:%S%z}", fmt::localtime(currentTime()));
    }
};
