#include "Benchmarking.h"

#include <fmt/color.h>
#include <fmt/format.h>

namespace Benchmark {

Timer::Timer(const std::string& name)
    : m_name(name)
{
    m_start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    // Print time in both milliseconds and nanoseconds.
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_start);
    fmt::print(fg(fmt::color::magenta), "[Benchmark] {} took {} ms ({} ns)\n", m_name, duration.count() / 1000000, duration.count());
}

} // namespace Benchmark
