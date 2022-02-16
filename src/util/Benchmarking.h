#pragma once

#include <chrono>
#include <string>

namespace Benchmark {

class ScopedTimer final {
public:
    explicit ScopedTimer(std::string &&name);

    ~ScopedTimer();

private:
    std::chrono::high_resolution_clock::time_point m_start;
    const std::string m_name;
};

} // namespace Benchmark
