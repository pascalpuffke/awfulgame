#pragma once

#include <chrono>
#include <string>

namespace Benchmark {

class Timer final {
public:
    Timer(const std::string& name);
    ~Timer();

private:
    std::chrono::high_resolution_clock::time_point m_start;
    const std::string m_name;
};

} // namespace Benchmark
